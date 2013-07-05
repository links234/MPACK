/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include <fstream>
#include <cassert>
#include <iostream>

#include "TargaImage.hpp"

#include "Resource.hpp"


namespace Core
{
	TargaImage::TargaImage()
	{
	}

	TargaImage::~TargaImage()
	{
		Unload();
	}

	Status TargaImage::Load(const string& filename)
	{
		Resource *resource=LoadResource(filename.c_str());

		if (resource->Open()!=STATUS_OK)
		{
			LOGE("Could not open the targa image file for reading");
			delete resource;
			return STATUS_KO;
		}

		unsigned char* pointer=(unsigned char*)resource->Bufferize();

		m_header=*((TargaHeader*)(pointer));
		pointer+=sizeof(TargaHeader);

		if (!IsImageTypeSupported(m_header))
		{
			LOGE("This is not a supported image type");
			delete resource;
			return STATUS_KO;
		}

		m_width = m_header.width;
		m_height = m_header.height;

		GLushort bitsPerPixel = m_header.bpp;
		m_bytesPerPixel = m_header.bpp / 8;

		if (m_bytesPerPixel < 3)
		{
			LOGE("Color depth not supported: %d",m_bytesPerPixel);
			delete resource;
			return STATUS_KO;
		}

		if(m_bytesPerPixel==3)
		{
			m_format=GL_RGB;
		}
		else if(m_bytesPerPixel==4)
		{
			m_format=GL_RGBA;
		}

		unsigned int imageSize = m_width * m_height * m_bytesPerPixel;

		m_imageData.resize(imageSize);

		if (m_header.idLength > 0)
		{
			pointer+=m_header.idLength;
		}

		bool result = false;

		if (IsUncompressedTarga(m_header))
		{
			result = LoadUncompressedTarga(pointer);
		}
		else
		{
			result = LoadCompressedTarga(pointer);
		}

		if ((m_header.imageDesc & TOP_LEFT) == TOP_LEFT)
		{
			FlipVertical();
		}

		delete resource;
		if(result)
		{
			return STATUS_OK;
		}
		return STATUS_KO;
	}

	void TargaImage::Unload()
	{
		m_imageData.clear();
	}

	const BYTE* TargaImage::GetImageData() const
	{
		return &m_imageData[0];
	}

	const BYTE* TargaImage::GetPixel(GLushort x, GLushort y) const
	{
		int index=x*m_width+y;
		index*=m_bytesPerPixel;
		return &m_imageData[index];
	}

	void TargaImage::FlipVertical()
	{
		vector<unsigned char> flippedData;
		flippedData.reserve(m_imageData.size());

		int step = m_bytesPerPixel;

		for (int row = m_height - 1; row >= 0; row--) {
			unsigned char* rowData = &m_imageData[row * m_width * step];
			for (unsigned int i = 0; i < m_width * step; ++i)  {
				flippedData.push_back(*rowData);
				rowData++;
			}
		}

		m_imageData.assign(flippedData.begin(), flippedData.end());
	}

	void TargaImage::FlipHorizontal()
	{
		vector<unsigned char> flippedData;
		flippedData.reserve(m_imageData.size());

		unsigned int step = m_bytesPerPixel;

		for (unsigned int row = 0; row <m_height; ++row) {
			unsigned char* rowData = &m_imageData[row * m_width * step];
			for (unsigned int i = m_width-1; i > 0; --i)  {
				for (unsigned int j = 0; i < step; ++j)
				{
					flippedData.push_back(*(rowData+i*step+j));
				}
			}
		}

		m_imageData.assign(flippedData.begin(), flippedData.end());
	}

	bool TargaImage::LoadCompressedTarga(unsigned char* pointer)
	{
		unsigned int pixelcount	= m_height * m_width;
		unsigned int currentpixel	= 0;
		unsigned int currentbyte	= 0;

		vector<unsigned char> colorBuffer(m_bytesPerPixel);

		do {
			unsigned char chunkheader = *(pointer);
			pointer+=sizeof(unsigned char);

			if(chunkheader < 128)
			{
				chunkheader++;

				for(short counter = 0; counter < chunkheader; counter++)
				{
					colorBuffer[0]=(unsigned char)(*pointer); ++pointer;
					colorBuffer[1]=(unsigned char)(*pointer); ++pointer;
					colorBuffer[2]=(unsigned char)(*pointer); ++pointer;

					if(m_bytesPerPixel == 4)
					{
						colorBuffer[3]=(unsigned char)(*pointer); ++pointer;
					}

					m_imageData[currentbyte] = colorBuffer[2];
					m_imageData[currentbyte + 1] = colorBuffer[1];
					m_imageData[currentbyte + 2] = colorBuffer[0];

					if(m_bytesPerPixel == 4)
					{
						m_imageData[currentbyte + 3] = colorBuffer[3];
					}

					currentbyte += m_bytesPerPixel;
					currentpixel++;

					if(currentpixel > pixelcount)
					{
						return false;
					}
				}
			}
			else
			{
				chunkheader -= 127;

				colorBuffer[0]=(unsigned char)(*pointer); ++pointer;
				colorBuffer[1]=(unsigned char)(*pointer); ++pointer;
				colorBuffer[2]=(unsigned char)(*pointer); ++pointer;

				if(m_bytesPerPixel == 4)
				{
					colorBuffer[4]=(unsigned char)(*pointer); ++pointer;
				}

				for(short counter = 0; counter < chunkheader; counter++)
				{
					m_imageData[currentbyte] = colorBuffer[2];
					m_imageData[currentbyte + 1] = colorBuffer[1];
					m_imageData[currentbyte + 2] = colorBuffer[0];

					if(m_bytesPerPixel == 4)
					{
						m_imageData[currentbyte + 3] = colorBuffer[3];
					}

					currentbyte += m_bytesPerPixel;
					currentpixel++;

					if(currentpixel > pixelcount)
					{
						return false;
					}
				}
			}
		} while(currentpixel < pixelcount);

		return true;
	}

	bool TargaImage::LoadUncompressedTarga(unsigned char *pointer)
	{
		unsigned int imageSize = m_imageData.size();
		m_imageData.assign((unsigned char*)pointer,(unsigned char*)(pointer+imageSize));

		for (unsigned int swap = 0; swap < imageSize; swap += m_bytesPerPixel)
		{
			char cswap = m_imageData[swap];
			m_imageData[swap] = m_imageData[swap + 2];
			m_imageData[swap + 2] = cswap;
		}

		return true;
	}

	bool TargaImage::IsImageTypeSupported(const TargaHeader& header)
	{

		if (((header.imageTypeCode != TFT_RGB) &&
			(header.imageTypeCode != TFT_RLE_RGB)) ||
			(header.colorMapType != 0))
		{
			return false;
		}

		return true;
	}

	bool TargaImage::IsCompressedTarga(const TargaHeader& header)
	{
		return (header.imageTypeCode == TFT_RLE_RGB ||
				header.imageTypeCode == TFT_RLE_GRAYSCALE);
	}

	bool TargaImage::IsUncompressedTarga(const TargaHeader& header)
	{
		return (header.imageTypeCode == TFT_RGB ||
				header.imageTypeCode == TFT_GRAYSCALE);
	}
}
