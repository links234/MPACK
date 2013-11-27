#ifndef PNGIMAGE_HPP
#define PNGIMAGE_HPP

#include "Image.hpp"
#include "Types.hpp"

#include <png.h>

namespace Core
{
    class PNGImage : public Image
    {
    public:
    	PNGImage();
		virtual ~PNGImage();

		ReturnValue Load(const string& filename);
		void Unload();

		const BYTE* GetImageData() const;
		const BYTE* GetPixel(GLushort x, GLushort y) const;

		void FlipVertical();
		void FlipHorizontal();

    private:
        static void callback_read(png_structp pStruct, png_bytep pData, png_size_t pSize);

    private:
        BYTE *m_imageBuffer;
    };
}
#endif
