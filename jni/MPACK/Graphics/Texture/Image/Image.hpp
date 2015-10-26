#ifndef MPACK_IMAGE_HPP
#define MPACK_IMAGE_HPP

#include "Types.hpp"

#include "Color.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Image
		{
		public:
			Image();
			virtual ~Image();

			virtual Core::ReturnValue Load(const std::string& filename) = 0;
			virtual void Unload() = 0;

			GLushort GetWidth() const;
			GLushort GetHeight() const;
			GLushort GetBytesPerPixel() const;

			GLint GetFormat() const;

			bool HaveAlphaChannel() const;

			virtual const BYTE* GetImageData() const = 0;
			virtual const BYTE* GetPixelPointer(GLushort x, GLushort y) const = 0;
			virtual Color GetPixel(GLushort x, GLushort y) const = 0;

			virtual void FlipVertical() = 0;
			virtual void FlipHorizontal() = 0;

		protected:
			GLushort m_width;
			GLushort m_height;
			GLushort m_format;
			GLushort m_bytesPerPixel;

			bool m_alphaChannel;
		};

		Image* LoadImage(const char *pPath);

		GLushort GetBPP(GLint format);
	}
}

#endif
