#ifndef MPACK_PNGIMAGE_HPP
#define MPACK_PNGIMAGE_HPP

#include "Image.hpp"
#include "Types.hpp"

#include <png.h>

namespace MPACK
{
	namespace Graphics
	{
		class PNGImage : public Image
		{
		public:
			PNGImage();
			virtual ~PNGImage();

			Core::ReturnValue Load(const std::string& filename);
			void Unload();

			const BYTE* GetImageData() const;
			const BYTE* GetPixelPointer(GLushort x, GLushort y) const;
			Color GetPixel(GLushort x, GLushort y) const;
			void SetPixel(GLushort x, GLushort y, Color c);

			void FlipVertical();
			void FlipHorizontal();

		private:
			static void callback_read(png_structp pStruct, png_bytep pData, png_size_t pSize);

			BYTE *m_imageBuffer;
		};
	}
}

#endif
