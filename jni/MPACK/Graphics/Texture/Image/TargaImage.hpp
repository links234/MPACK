/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MPACK_TARGAIMAGE_HPP
#define MPACK_TARGAIMAGE_HPP

#include "Image.hpp"
#include "Types.hpp"

#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::istream;

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

		class TargaImage : public Image
		{
		public:
			TargaImage();
			virtual ~TargaImage();

			Core::ReturnValue Load(const string& filename);
			void Unload();

			const BYTE* GetImageData() const;
			const BYTE* GetPixel(GLushort x, GLushort y) const;

			void FlipVertical();
			void FlipHorizontal();

		private:
			TargaHeader m_header;

			vector<unsigned char> m_imageData;

			bool LoadUncompressedTarga(unsigned char* pointer);
			bool LoadCompressedTarga(unsigned char* pointer);

			bool IsImageTypeSupported(const TargaHeader& header);
			bool IsCompressedTarga(const TargaHeader& header);
			bool IsUncompressedTarga(const TargaHeader& header);
		};
	}
}

#endif 
