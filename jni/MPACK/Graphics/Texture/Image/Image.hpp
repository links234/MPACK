#ifndef MPACK_IMAGE_HPP
#define MPACK_IMAGE_HPP

#include "Types.hpp"

#include "Color.hpp"
#include "Rect.hpp"

namespace MPACK
{
	namespace Graphics
	{
		typedef MPACK::Math::Vector2<int> Point;

		class Image
		{
		public:
			Image();
			virtual ~Image();

			virtual void Init(const int &width, const int &height) = 0;
			virtual Core::ReturnValue Load(const std::string& filename) = 0;
			virtual void Unload() = 0;

			void InitColor(const int &width, const int &height, const Color &c);
			void FillColor(const Rect &rect, const Color &c);

			GLushort GetWidth() const;
			GLushort GetHeight() const;
			GLushort GetBytesPerPixel() const;

			GLint GetFormat() const;

			bool HaveAlphaChannel() const;

			virtual const BYTE* GetImageData() const = 0;
			virtual const BYTE* GetPixelPointer(const GLushort &x, const GLushort &y) const = 0;
			virtual Color GetPixel(const GLushort &x, const GLushort &y) const = 0;
			virtual void SetPixel(const GLushort &x, const GLushort &y, const Color &c) = 0;

			virtual void FlipVertical() = 0;
			virtual void FlipHorizontal() = 0;

			void Blit(Image *image, const GLushort &x, const GLushort &y);
			void Blit(Image *image, const Point &point);
			void Blit(Image *image, const Point &point, const Rect &rect);

		protected:
			void BlitSafe(Image *image, Point point, Rect rect);

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
