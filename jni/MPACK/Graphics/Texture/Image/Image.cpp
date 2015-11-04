#include "Image.hpp"

#include "StringEx.hpp"
#include "TargaImage.hpp"
#include "PNGImage.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Graphics
	{
		Image::Image()
			: m_width(0), m_height(0), m_format(0), m_bytesPerPixel(0),
			  m_alphaChannel(false)
		{
		}

		Image::~Image()
		{
		}

		void Image::InitColor(const int &width, const int &height, const Color &c)
		{
			Init(width, height);
			FillColor(Rect(0, 0, m_width, m_height), c);
		}

		void Image::FillColor(const Rect &rect, const Color &c)
		{
			for(int i = 0; i < m_height; ++i)
			{
				for(int j = 0; j < m_width; ++j)
				{
					SetPixel(rect.x + i, rect.y + j, c);
				}
			}
		}

		GLushort Image::GetWidth() const
		{
			return m_width;
		}

		GLushort Image::GetHeight() const
		{
			return m_height;
		}

		GLushort Image::GetBytesPerPixel() const
		{
			return m_bytesPerPixel;
		}

		GLint Image::GetFormat() const
		{
			return m_format;
		}

		bool Image::HaveAlphaChannel() const
		{
			return m_alphaChannel;
		}

		Image* LoadImage(const char *pPath)
		{
			string ext;
			Core::StringEx::GetExtension(pPath,ext);
			Core::StringEx::Upper(ext);
			Image *image=NULL;
			if(ext=="TGA")
			{
				image=new TargaImage;
			}
			else if(ext=="PNG")
			{
				image=new PNGImage;
			}

			if(!image)
			{
				LOGE("LoadImage: invalid format %s",pPath);
				return NULL;
			}
			if(image->Load(pPath)==RETURN_VALUE_KO)
			{
				LOGE("LoadImage: Failed to load");
				delete image;
				image=NULL;
			}
			return image;
		}

		GLushort GetBPP(GLint format)
		{
			switch(format)
			{
				case GL_RGB:
					return 3;
				break;
				case GL_RGBA:
					return 4;
				break;
				case GL_LUMINANCE:
					return 1;
				break;
				case GL_LUMINANCE_ALPHA:
					return 2;
				break;
			}
			return 0;
		}

		void Image::Blit(Image *image, const GLushort &x, const GLushort &y)
		{
			BlitSafe(image, Point(x,y), Rect(0,0,image->GetWidth(),image->GetHeight()));
		}

		void Image::Blit(Image *image, const Point &point)
		{
			BlitSafe(image, point, Rect(0,0,image->GetWidth(),image->GetHeight()));
		}

		void Image::Blit(Image *image, const Point &point, const Rect &rect)
		{
			BlitSafe(image, point, rect);
		}

		void Image::BlitSafe(Image *image, Point point, Rect rect)
		{
			GLushort width = image->GetWidth();
			GLushort height = image->GetHeight();

			if (point.x >= m_width || point.y >= m_height)
			{
				return;
			}

			if (rect.width <= 0 || rect.height <= 0)
			{
				return;
			}

			if (rect.x >= width || rect.y >= height)
			{
				return;
			}

			if (point.x < 0)
			{
				point.x = 0;
			}

			if (point.y < 0)
			{
				point.y = 0;
			}

			GLushort maxWidth = m_width - point.x;
			if (rect.width > maxWidth)
			{
				rect.width = maxWidth;
			}

			GLushort maxHeight = m_height - point.y;
			if (rect.height > maxHeight)
			{
				rect.height = maxHeight - point.y;
			}

			for (int i = 0; i < rect.height; ++i)
			{
				for (int j = 0; j < rect.width; ++j)
				{
					SetPixel(point.x + i, point.y + j, image->GetPixel(i + rect.x, j + rect.y));
				}
			}
		}
	}
}
