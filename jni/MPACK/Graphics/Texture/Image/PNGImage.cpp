#include "PNGImage.hpp"

#include <png.h>

#include "Image.hpp"
#include "Resources.hpp"
#include "Misc.hpp"
#include "Log.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Graphics
	{
		void LoadPNG_CallbackRead(png_structp pStruct, png_bytep pData, png_size_t pSize)
		{
			InputResource* pInputResource = ((InputResource*) png_get_io_ptr(pStruct));
			if (pInputResource->Read(pData, pSize) != RETURN_VALUE_OK)
			{
				pInputResource->Close();
			}
		}

		ReturnValue LoadPNG(Image *image, const std::string &path)
		{
			image->Unload();

			LOGI("LoadPNG() loading image %s", path.c_str());

			InputResource *pInputResource = GetInputResource(path.c_str());

			png_byte header[8];
			png_structp pngPtr = NULL;
			png_infop infoPtr = NULL;
			png_bytep* rowPtrs = NULL;
			png_int_32 rowSize;
			bool transparency;

			if (pInputResource->Open() != RETURN_VALUE_OK)
			{
				goto ERROR_LABEL;
			}

			if (pInputResource->Read(header, sizeof(header)) != RETURN_VALUE_OK)
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
				LOGE("LoadPNG() failed to create read structure!");
				goto ERROR_LABEL;
			}
			infoPtr = png_create_info_struct(pngPtr);

			if (!infoPtr)
			{
				goto ERROR_LABEL;
			}

			png_set_read_fn(pngPtr, pInputResource, LoadPNG_CallbackRead);
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
			image->m_width = width;
			image->m_height = height;

			// Creates a full alpha channel if transparency is encoded as
			// an array of palette entries or a single transparent color.
			transparency = false;
			if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS))
			{
				png_set_tRNS_to_alpha(pngPtr);
				transparency = true;
				goto ERROR_LABEL;
			}

			if (depth < 8)
			{
				png_set_packing (pngPtr);
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
					image->m_GLFormatType = transparency ? GL_RGBA : GL_RGB;
					image->m_internalFormatType = transparency ? Image::InternalFormatType::RGBA : Image::InternalFormatType::RGB;
				break;
				case PNG_COLOR_TYPE_RGB:
					image->m_GLFormatType = transparency ? GL_RGBA : GL_RGB;
					image->m_internalFormatType = transparency ? Image::InternalFormatType::RGBA : Image::InternalFormatType::RGB;
				break;
				case PNG_COLOR_TYPE_RGBA:
					image->m_GLFormatType = GL_RGBA;
					image->m_internalFormatType = Image::InternalFormatType::RGBA;
				break;
				case PNG_COLOR_TYPE_GRAY:
					png_set_expand_gray_1_2_4_to_8(pngPtr);
					image->m_GLFormatType = transparency ? GL_LUMINANCE_ALPHA : GL_LUMINANCE;
					image->m_internalFormatType = transparency ? Image::InternalFormatType::GRAY_ALPHA : Image::InternalFormatType::GRAY;
				break;
				case PNG_COLOR_TYPE_GRAY_ALPHA:
					png_set_expand_gray_1_2_4_to_8(pngPtr);
					image->m_GLFormatType = GL_LUMINANCE_ALPHA;
					image->m_internalFormatType = Image::InternalFormatType::GRAY_ALPHA;
				break;
			}
			// Validates all tranformations.
			png_read_update_info(pngPtr, infoPtr);

			image->m_bytesPerPixel=GetBPP(image->m_GLFormatType);

			// Get row size in bytes.
			rowSize = png_get_rowbytes(pngPtr, infoPtr);
			if (rowSize <= 0)
			{
				goto ERROR_LABEL;
			}
			// Ceates the image buffer that will be sent to OpenGL.
			image->m_imageBuffer = new png_byte[rowSize * height];
			if (!image->m_imageBuffer)
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
				rowPtrs[height - (i + 1)] = image->m_imageBuffer + i * rowSize;
			}
			// Reads image content.
			png_read_image(pngPtr, rowPtrs);

			// Frees memory and resources.
			pInputResource->Close();
			delete pInputResource;
			png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
			delete[] rowPtrs;
			return RETURN_VALUE_OK;

	ERROR_LABEL:
			LOGE("LoadPNG() error while reading PNG file");
			pInputResource->Close();
			delete pInputResource;
			if(rowPtrs)
			{
				delete[] rowPtrs;
			}
			if(pngPtr)
			{
				png_infop* infoPtrP = infoPtr != NULL ? &infoPtr: NULL;
				png_destroy_read_struct(&pngPtr, infoPtrP, NULL);
			}
			image->Unload();
			return RETURN_VALUE_KO;
		}

		ReturnValue SavePNG(Image *image, const std::string &path)
		{
			ReturnValue returnValue = RETURN_VALUE_OK;
			FILE *pFile = NULL;
			png_structp pPng = NULL;
			png_infop pPngInfo = NULL;
			png_bytep pRow = NULL;

			int colorType = PNG_COLOR_TYPE_RGB_ALPHA;

			pFile = fopen(path.c_str(), "wb");
			if (pFile == NULL)
			{
				LOGE("SavePNG() could not open file %s for writing", path.c_str());
				returnValue = RETURN_VALUE_KO;
				goto SAVEPNG_CLEANUP;
			}

			pPng = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (pPng == NULL)
			{
				LOGE("SavePNG() could not allocate write struct");
				returnValue = RETURN_VALUE_KO;
				goto SAVEPNG_CLEANUP;
			}

			pPngInfo = png_create_info_struct(pPng);
			if (pPngInfo == NULL)
			{
				LOGE("SavePNG() could not allocate png info struct");
				returnValue = RETURN_VALUE_KO;
				goto SAVEPNG_CLEANUP;
			}

			if (setjmp(png_jmpbuf(pPng)))
			{
				LOGE("SavePNG() error during png creation");
				returnValue = RETURN_VALUE_KO;
				goto SAVEPNG_CLEANUP;
			}

			png_init_io(pPng, pFile);

			if (image->m_bytesPerPixel == 1)
			{
				colorType = PNG_COLOR_TYPE_GRAY;
			}
			else if(image->m_bytesPerPixel == 2)
			{
				colorType = PNG_COLOR_TYPE_GRAY_ALPHA;
			}
			else if(image->m_bytesPerPixel == 3)
			{
				colorType = PNG_COLOR_TYPE_RGB;
			}

			png_set_IHDR(pPng, pPngInfo, image->m_width, image->m_height,
						 8, colorType, PNG_INTERLACE_NONE,
						 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

			png_write_info(pPng, pPngInfo);

			for (int y = 0 ; y < image->m_height ; ++y)
			{
				pRow = image->m_imageBuffer + image->m_width * y * image->m_bytesPerPixel;
				png_write_row(pPng, pRow);
			}

			png_write_end(pPng, NULL);

		SAVEPNG_CLEANUP:
			if (pFile != NULL)
			{
				fclose(pFile);
			}
			if (pPngInfo != NULL)
			{
				png_free_data(pPng, pPngInfo, PNG_FREE_ALL, -1);
			}
			if (pPng != NULL)
			{
				png_destroy_write_struct(&pPng, (png_infopp)NULL);
			}

			return returnValue;
		}
	}
}
