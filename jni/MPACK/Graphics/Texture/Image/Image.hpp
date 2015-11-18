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
			enum InternalFormatType {NONE, GRAY, GRAY_ALPHA, RGB, RGBA};
			enum FileFormatType {AUTO, PNG, TGA, PPM};

			Image();
			~Image();

			void Init(const int &width, const int &height);
			Core::ReturnValue Load(const std::string& path, bool flipForOpenGL = true, FileFormatType fileFormatType = AUTO);
			Core::ReturnValue Save(const std::string& path, FileFormatType fileFormatType = AUTO);
			void Unload();

			void InitColor(const int &width, const int &height, const Color &c);
			void FillColor(const Rect &rect, const Color &c);

			void Blit(Image *image, const GLushort &x, const GLushort &y);
			void Blit(Image *image, const Point &point);
			void Blit(Image *image, const Point &point, const Rect &rect);

			void FlipVertical();
			void FlipHorizontal();

			GLushort GetWidth() const;
			GLushort GetHeight() const;
			GLushort GetBytesPerPixel() const;

			GLint GetGLFormat() const;
			InternalFormatType GetFormat() const;

			bool HaveAlphaChannel() const;

			const BYTE* GetImageData() const;
			const BYTE* GetPixelPointer(const GLushort &x, const GLushort &y) const;
			Color GetPixel(const GLushort &x, const GLushort &y) const;
			void SetPixel(const GLushort &x, const GLushort &y, const Color &c);

		protected:
			void BlitSafe(Image *image, Point point, Rect rect);

			GLushort m_width;
			GLushort m_height;
			GLushort m_GLFormatType;
			GLushort m_bytesPerPixel;

			InternalFormatType m_internalFormatType;

			BYTE *m_imageBuffer;

			friend Core::ReturnValue LoadTGA(Image *image, const std::string &path, bool flipForOpenGL);
			friend Core::ReturnValue SaveTGA(Image *image, const std::string &path);

			friend Core::ReturnValue LoadPNG(Image *image, const std::string &path, bool flipForOpenGL);
			friend Core::ReturnValue SavePNG(Image *image, const std::string &path);

			friend Core::ReturnValue LoadPPM(Image *image, const std::string &path, bool flipForOpenGL);
			friend Core::ReturnValue SavePPM(Image *image, const std::string &path);
		};

		GLushort GetBPP(GLint format);
	}
}

#endif
