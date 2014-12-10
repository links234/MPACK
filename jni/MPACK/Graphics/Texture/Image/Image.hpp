#ifndef MPACK_IMAGE_HPP
#define MPACK_IMAGE_HPP

#include "Types.hpp"

using namespace std;

namespace Core
{
	class Image
	{
	public:
		Image();
		virtual ~Image();

		virtual ReturnValue Load(const string& filename) = 0;
		virtual void Unload() = 0;

		GLushort GetWidth() const;
		GLushort GetHeight() const;
		GLushort GetBytesPerPixel() const;

		GLint GetFormat() const;

		virtual const BYTE* GetImageData() const = 0;
		virtual const BYTE* GetPixel(GLushort x, GLushort y) const = 0;

		virtual void FlipVertical() = 0;
		virtual void FlipHorizontal() = 0;

	protected:
		GLushort m_width;
		GLushort m_height;
		GLushort m_format;
		GLushort m_bytesPerPixel;


	};

	Image* LoadImage(const char *pPath);

	GLushort GetBPP(GLint format);
}

#endif
