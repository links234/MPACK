#include "TargaImage.hpp"

#include "Image.hpp"
#include "Resources.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Graphics
	{
		enum IMAGE_ORIENTATIONS
		{
			BOTTOM_LEFT = 0x00,
			BOTTOM_RIGHT = 0x10,
			TOP_LEFT = 0x20,
			TOP_RIGHT = 0x30
		};

		struct TargaHeader
		{
			unsigned char idLength;
			unsigned char colorMapType;
			unsigned char imageTypeCode;
			unsigned char colorMapSpec[5];
			unsigned short xOrigin;
			unsigned short yOrigin;
			unsigned short width;
			unsigned short height;
			unsigned char bpp;
			unsigned char imageDesc;
		};

		enum TargaFileTypes
		{
			TFT_NO_DATA = 0,
			TFT_INDEXED = 1,
			TFT_RGB = 2,
			TFT_GRAYSCALE = 3,
			TFT_RLE_INDEXED = 9,
			TFT_RLE_RGB = 10,
			TFT_RLE_GRAYSCALE = 11
		};

		bool IsImageTypeSupported(const TargaHeader& header)
		{

			if (((header.imageTypeCode != TFT_RGB) &&
				(header.imageTypeCode != TFT_RLE_RGB)) ||
				(header.colorMapType != 0))
			{
				return false;
			}

			return true;
		}

		bool IsCompressedTarga(const TargaHeader& header)
		{
			return (header.imageTypeCode == TFT_RLE_RGB ||
					header.imageTypeCode == TFT_RLE_GRAYSCALE);
		}

		bool IsUncompressedTarga(const TargaHeader& header)
		{
			return (header.imageTypeCode == TFT_RGB ||
					header.imageTypeCode == TFT_GRAYSCALE);
		}

		Core::ReturnValue LoadTGA(Image *image, const string& path, bool flipForOpenGL)
		{
			image->Unload();

			InputResource *pInputResource=GetInputResource(path.c_str());

			if (pInputResource->Open()!=RETURN_VALUE_OK)
			{
				LOGE("LoadTGA() Could not open the file for reading");
				delete pInputResource;
				return RETURN_VALUE_KO;
			}

			unsigned char* pointer = (unsigned char*)pInputResource->Bufferize();


			TargaHeader header = *((TargaHeader*)(pointer));
			pointer += sizeof(TargaHeader);

			if (!IsImageTypeSupported(header))
			{
				LOGE("LoadTGA() This is not a supported image type");
				delete pInputResource;
				return RETURN_VALUE_KO;
			}

			image->m_width = header.width;
			image->m_height = header.height;

			GLushort bitsPerPixel = header.bpp;
			image->m_bytesPerPixel = bitsPerPixel / 8;

			if (image->m_bytesPerPixel < 3)
			{
				LOGE("LoadTGA() format unsupported (bytes per pixel: %d)", image->m_bytesPerPixel);
				delete pInputResource;
				return RETURN_VALUE_KO;
			}

			if(image->m_bytesPerPixel == 3)
			{
				image->m_GLFormatType = GL_RGB;
				image->m_internalFormatType = Image::InternalFormatType::RGB;
			}
			else if(image->m_bytesPerPixel == 4)
			{
				image->m_GLFormatType = GL_RGBA;
				image->m_internalFormatType = Image::InternalFormatType::RGBA;
			}

			unsigned int imageSize = image->m_width * image->m_height * image->m_bytesPerPixel;

			image->m_imageBuffer = new BYTE[imageSize];
			if (header.idLength > 0)
			{
				pointer += header.idLength;
			}

			bool result = true;

			if (IsUncompressedTarga(header))
			{
				memcpy(image->m_imageBuffer, pointer, imageSize);

				for (unsigned int index = 0; index < imageSize; index += image->m_bytesPerPixel)
				{
					swap(image->m_imageBuffer[index], image->m_imageBuffer[index + 2]);
				}
			}
			else
			{
				unsigned int pixelcount	= image->m_height * image->m_width;
				unsigned int currentpixel = 0;
				unsigned int currentbyte = 0;

				unsigned char colorBuffer[4];

				do {
					unsigned char chunkheader = *(pointer);
					pointer+=sizeof(unsigned char);

					if(chunkheader < 128)
					{
						chunkheader++;

						for(short counter = 0; counter < chunkheader; counter++)
						{
							image->m_imageBuffer[currentbyte] = (*pointer);
							++pointer;
							image->m_imageBuffer[currentbyte + 1] = (*pointer);
							++pointer;
							image->m_imageBuffer[currentbyte + 2] = (*pointer);
							++pointer;

							if(image->m_bytesPerPixel == 4)
							{
								image->m_imageBuffer[currentbyte + 3] = (*pointer);
								++pointer;
							}

							currentbyte += image->m_bytesPerPixel;
							currentpixel++;

							if(currentpixel > pixelcount)
							{
								result = false;
								goto LOADTGA_ERROR;
							}
						}
					}
					else
					{
						chunkheader -= 127;

						colorBuffer[0]=(unsigned char)(*pointer); ++pointer;
						colorBuffer[1]=(unsigned char)(*pointer); ++pointer;
						colorBuffer[2]=(unsigned char)(*pointer); ++pointer;

						if(image->m_bytesPerPixel == 4)
						{
							colorBuffer[3]=(unsigned char)(*pointer); ++pointer;
						}

						for(short counter = 0; counter < chunkheader; counter++)
						{
							image->m_imageBuffer[currentbyte] = colorBuffer[2];
							image->m_imageBuffer[currentbyte + 1] = colorBuffer[1];
							image->m_imageBuffer[currentbyte + 2] = colorBuffer[0];

							if(image->m_bytesPerPixel == 4)
							{
								image->m_imageBuffer[currentbyte + 3] = colorBuffer[3];
							}

							currentbyte += image->m_bytesPerPixel;
							currentpixel++;

							if(currentpixel > pixelcount)
							{
								result = false;
								goto LOADTGA_ERROR;
							}
						}
					}
				} while(currentpixel < pixelcount);
			}
			if ((header.imageDesc & TOP_LEFT) == TOP_LEFT)
			{
				if (flipForOpenGL)
				{
					image->FlipVertical();
				}
			}
			else
			{
				if(!flipForOpenGL)
				{
					image->FlipVertical();
				}
			}
		LOADTGA_ERROR:
			delete pInputResource;
			if (!result)
			{
				LOGE("LoadTGA() fail: corrupt file");
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		Core::ReturnValue SaveTGA(Image *image, const string& path)
		{
			LOGE("SaveTGA() error: not implemented");
			return RETURN_VALUE_KO;
		}
	}
}
