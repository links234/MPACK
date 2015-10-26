#include "PNGImage.hpp"

#include "Resource.hpp"
#include "SDInputFile.hpp"
#include "Asset.hpp"
#include "Misc.hpp"
#include "Log.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Graphics
	{
		PNGImage::PNGImage()
			: m_imageBuffer(NULL)
		{
		}

		PNGImage::~PNGImage()
		{
			Unload();
		}

		ReturnValue PNGImage::Load(const std::string& filename)
		{
			LOGI("PNGImage::Load Loading texture %s", filename.c_str());

			Resource *pResource=LoadResource(filename.c_str());

			png_byte header[8];
			png_structp pngPtr = NULL;
			png_infop infoPtr = NULL;
			png_bytep* rowPtrs = NULL;
			png_int_32 rowSize;
			bool transparency;

			// Opens and checks image signature (first 8 bytes).
			if (pResource->Open() != RETURN_VALUE_OK)
			{
				goto ERROR_LABEL;
			}

			if (pResource->Read(header, sizeof(header)) != RETURN_VALUE_OK)
			{
				goto ERROR_LABEL;
			}
			if (png_sig_cmp(header, 0, 8) != 0)
			{
				goto ERROR_LABEL;
			}

			// Creates required structures.
			pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (!pngPtr)
			{
				LOGE("PNGImage::Load failed to create read structure!");
				goto ERROR_LABEL;
			}
			infoPtr = png_create_info_struct(pngPtr);

			if (!infoPtr)
			{
				goto ERROR_LABEL;
			}

			// Prepares reading operation by setting-up a read callback.
			png_set_read_fn(pngPtr, pResource, callback_read);
			// Set-up error management. If an error occurs while reading,
			// code will come back here and jump
			if (setjmp(png_jmpbuf(pngPtr)))
			{
				goto ERROR_LABEL;
			}

			// Ignores first 8 bytes already read and processes header.
			png_set_sig_bytes(pngPtr, 8);
			png_read_info(pngPtr, infoPtr);
			// Retrieves PNG info and updates PNG struct accordingly.
			int depth, colorType;
			png_uint_32 width, height;
			png_get_IHDR(pngPtr, infoPtr, &width, &height, &depth, &colorType, NULL, NULL, NULL);
			m_width = width; m_height = height;

			// Creates a full alpha channel if transparency is encoded as
			// an array of palette entries or a single transparent color.
			transparency = false;
			if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS))
			{
				png_set_tRNS_to_alpha(pngPtr);
				transparency = true;
				return RETURN_VALUE_KO;
							//goto ERROR_LABEL;
			}

			// Expands PNG with less than 8bits per channel to 8bits.
			if (depth < 8)
			{
				png_set_packing (pngPtr);
			// Shrinks PNG with 16bits per color channel down to 8bits.
			}
			else if (depth == 16)
			{
				png_set_strip_16(pngPtr);
			}
			// Indicates that image needs conversion to RGBA if needed.

			switch (colorType)
			{
				case PNG_COLOR_TYPE_PALETTE:
					png_set_palette_to_rgb(pngPtr);
					m_format = transparency ? GL_RGBA : GL_RGB;
					break;
				case PNG_COLOR_TYPE_RGB:
					m_format = transparency ? GL_RGBA : GL_RGB;
					break;
				case PNG_COLOR_TYPE_RGBA:
					m_format = GL_RGBA;
					break;
				case PNG_COLOR_TYPE_GRAY:
					png_set_expand_gray_1_2_4_to_8(pngPtr);
					m_format = transparency ? GL_LUMINANCE_ALPHA:GL_LUMINANCE;
					break;
				case PNG_COLOR_TYPE_GA:
					png_set_expand_gray_1_2_4_to_8(pngPtr);
					m_format = GL_LUMINANCE_ALPHA;
					break;
			}
			// Validates all tranformations.
			png_read_update_info(pngPtr, infoPtr);

			m_bytesPerPixel=GetBPP(m_format);

			// Get row size in bytes.
			rowSize = png_get_rowbytes(pngPtr, infoPtr);
			if (rowSize <= 0)
			{
				goto ERROR_LABEL;
			}
			// Ceates the image buffer that will be sent to OpenGL.
			m_imageBuffer = new png_byte[rowSize * height];
			if (!m_imageBuffer)
			{
				goto ERROR_LABEL;
			}
			// Pointers to each row of the image buffer. Row order is
			// inverted because different coordinate systems are used by
			// OpenGL (1st pixel is at bottom left) and PNGs (top-left).
			rowPtrs = new png_bytep[height];
			if (!rowPtrs)
			{
				goto ERROR_LABEL;
			}
			for (::int32_t i = 0; i < height; ++i)
			{
				rowPtrs[height - (i + 1)] = m_imageBuffer + i * rowSize;
			}
			// Reads image content.
			png_read_image(pngPtr, rowPtrs);

			// Frees memory and resources.
			pResource->Close();
			delete pResource;
			png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
			delete[] rowPtrs;
			return RETURN_VALUE_OK;

	ERROR_LABEL:
			LOGE("Error while reading PNG file");
			pResource->Close();
			delete pResource;
			if(rowPtrs)
			{
				delete[] rowPtrs;
			}
			if(m_imageBuffer)
			{
				delete[] m_imageBuffer;
			}
			if(pngPtr)
			{
				png_infop* infoPtrP = infoPtr != NULL ? &infoPtr: NULL;
				png_destroy_read_struct(&pngPtr, infoPtrP, NULL);
			}
			return RETURN_VALUE_KO;
		}

		void PNGImage::Unload()
		{
			m_width=0;
			m_height=0;
			m_format=0;
			delete[] m_imageBuffer;
		}

		const BYTE* PNGImage::GetImageData() const
		{
			return m_imageBuffer;
		}

		const BYTE* PNGImage::GetPixel(GLushort x, GLushort y) const
		{
			int index=x*m_width+y;
			index*=m_bytesPerPixel;
			return m_imageBuffer+index;
		}

		void PNGImage::FlipVertical()
		{
			for(int i=0;i<(m_width>>1);++i)
			{
				for(int j=0;j<m_height;++j)
				{
					int offset1=i*m_width+j;
					offset1*=m_bytesPerPixel;

					int vi=m_width-i-1;
					int vj=j;

					int offset2=vi*m_width+vj;
					offset2*=m_bytesPerPixel;

					StringEx::MemSwap((char*)(m_imageBuffer+offset1),(char*)(m_imageBuffer+offset2),m_bytesPerPixel);
				}
			}
		}

		void PNGImage::FlipHorizontal()
		{
			for(int i=0;i<m_width;++i)
			{
				for(int j=0;j<(m_height>>1);++j)
				{
					int offset1=i*m_width+j;
					offset1*=m_bytesPerPixel;

					int vi=i;
					int vj=m_height-j+1;

					int offset2=vi*m_width+vj;
					offset2*=m_bytesPerPixel;

					StringEx::MemSwap((char*)(m_imageBuffer+offset1),(char*)(m_imageBuffer+offset2),m_bytesPerPixel);
				}
			}
		}

		void PNGImage::callback_read(png_structp pStruct, png_bytep pData, png_size_t pSize)
		{
			Resource* lResource = ((Resource*) png_get_io_ptr(pStruct));
			if (lResource->Read(pData, pSize) != RETURN_VALUE_OK)
			{
				lResource->Close();
			}
		}
	}
}
