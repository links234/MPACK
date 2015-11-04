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

			void Init(const int &width, const int &height);
			Core::ReturnValue Load(const std::string& filename);
			void Unload();

			const BYTE* GetImageData() const;
			const BYTE* GetPixelPointer(const GLushort &x, const GLushort &y) const;
			Color GetPixel(const GLushort &x, const GLushort &y) const;
			void SetPixel(const GLushort &x, const GLushort &y, const Color &c);

			Core::ReturnValue SavePNG(const std::string &path);

			void FlipVertical();
			void FlipHorizontal();

		private:
			static void callback_read(png_structp pStruct, png_bytep pData, png_size_t pSize);

			BYTE *m_imageBuffer;
		};
	}
}

#endif
