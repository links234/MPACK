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
			: m_width(0), m_height(0), m_GLFormatType(0), m_bytesPerPixel(0),
			  m_imageBuffer(NULL), m_internalFormatType(Image::InternalFormatType::NONE)
		{
		}

		Image::~Image()
		{
			Unload();
		}

		void Image::Init(const int &width, const int &height)
		{
			Unload();

			if (width < 0)
			{
				LOGW("PNGImage::Init() invalid width!");
				m_width = 1;
			}
			else
			{
				m_width = width;
			}

			if (height < 0)
			{
				LOGW("PNGImage::Init() invalid height!");
				m_height = 1;
			}
			else
			{
				m_height = height;
			}

			m_bytesPerPixel = 4;
			m_GLFormatType = GL_RGBA;

			m_imageBuffer = new BYTE[m_width * m_height * m_bytesPerPixel];
		}

		ReturnValue Image::Load(const std::string& path, bool flipForOpenGL, FileFormatType fileFormatType)
		{
			Unload();

			if (fileFormatType == FileFormatType::AUTO)
			{
				string ext;
				Core::StringEx::GetExtension(path.c_str(), ext);
				Core::StringEx::Upper(ext);
				if(ext == "TGA")
				{
					fileFormatType = FileFormatType::TGA;
				}
				else if(ext == "PNG")
				{
					fileFormatType = FileFormatType::PNG;
				}
				else if(ext == "PPM")
				{
					fileFormatType = FileFormatType::PPM;
				}
				else
				{
					LOGE("Image::Load() format auto-detect fail: invalid extension: %s", path.c_str());
					return RETURN_VALUE_KO;
				}
			}

			switch(fileFormatType)
			{
				case FileFormatType::TGA:
					if (LoadTGA(this, path, flipForOpenGL) == RETURN_VALUE_KO)
					{
						LOGE("Image::Load() fail to load TGA image: %s", path.c_str());
						return RETURN_VALUE_KO;
					}
				break;
				case FileFormatType::PNG:
					if (LoadPNG(this, path, flipForOpenGL) == RETURN_VALUE_KO)
					{
						LOGE("Image::Load() fail to load PNG image: %s", path.c_str());
						return RETURN_VALUE_KO;
					}
				break;
				case FileFormatType::PPM:
					if (LoadPPM(this, path, flipForOpenGL) == RETURN_VALUE_KO)
					{
						LOGE("Image::Load() fail to load PPM image: %s", path.c_str());
						return RETURN_VALUE_KO;
					}
				break;
			}

			return RETURN_VALUE_OK;
		}

		ReturnValue Image::Save(const std::string& path, FileFormatType fileFormatType)
		{
			if (fileFormatType == FileFormatType::AUTO)
			{
				fileFormatType = FileFormatType::PNG;
			}

			switch(fileFormatType)
			{
				case FileFormatType::TGA:
					if (SaveTGA(this, path) == RETURN_VALUE_KO)
					{
						LOGE("Image::Save() fail to save image as TGA");
						return RETURN_VALUE_KO;
					}
				break;
				case FileFormatType::PNG:
					if (SavePNG(this, path) == RETURN_VALUE_KO)
					{
						LOGE("Image::Save() fail to save image as PNG");
						return RETURN_VALUE_KO;
					}
				break;
				case FileFormatType::PPM:
					if (SavePPM(this, path) == RETURN_VALUE_KO)
					{
						LOGE("Image::Save() fail to save image as PPM");
						return RETURN_VALUE_KO;
					}
				break;
			}
			return RETURN_VALUE_OK;
		}

		void Image::Unload()
		{
			if (m_imageBuffer)
			{
				m_width = 0;
				m_height = 0;
				m_internalFormatType = InternalFormatType::NONE;
				m_GLFormatType = 0;
				m_bytesPerPixel = 0;
				delete[] m_imageBuffer;
				m_imageBuffer = 0;
			}
		}

		void Image::InitColor(const int &width, const int &height, const Color &c)
		{
			Init(width, height);
			FillColor(Rect(0, 0, m_width, m_height), c);
		}

		void Image::FillColor(const Rect &rect, const Color &c)
		{
			for(int i = 0; i < m_width; ++i)
			{
				for(int j = 0; j < m_height; ++j)
				{
					SetPixel(rect.x + i, rect.y + j, c);
				}
			}
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

		void Image::FlipVertical()
		{
			for(int i = 0; i < (m_width >> 1); ++i)
			{
				for(int j = 0; j < m_height; ++j)
				{
					int offset1 = i * m_width + j;
					offset1 *= m_bytesPerPixel;

					int vi = m_width - i - 1;
					int vj = j;

					int offset2 = vi * m_width + vj;
					offset2 *= m_bytesPerPixel;

					StringEx::MemSwap((char*)(m_imageBuffer + offset1),(char*)(m_imageBuffer + offset2),m_bytesPerPixel);
				}
			}
		}

		void Image::FlipHorizontal()
		{
			for(int i = 0; i < m_width; ++i)
			{
				for(int j = 0; j < (m_height >> 1); ++j)
				{
					int offset1 = i * m_width + j;
					offset1 *= m_bytesPerPixel;

					int vi = i;
					int vj = m_height - j + 1;

					int offset2 = vi * m_width + vj;
					offset2 *= m_bytesPerPixel;

					StringEx::MemSwap((char*)(m_imageBuffer + offset1),(char*)(m_imageBuffer + offset2),m_bytesPerPixel);
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

		GLint Image::GetGLFormat() const
		{
			return m_GLFormatType;
		}

		Image::InternalFormatType Image::GetFormat() const
		{
			return m_internalFormatType;
		}

		bool Image::HaveAlphaChannel() const
		{
			return m_internalFormatType == Image::InternalFormatType::GRAY_ALPHA ||
				   m_internalFormatType == Image::InternalFormatType::RGBA;
		}

		const BYTE* Image::GetImageData() const
		{
			return m_imageBuffer;
		}

		const BYTE* Image::GetPixelPointer(const GLushort &x, const GLushort &y) const
		{
			int index = y * m_width + x;
			index *= m_bytesPerPixel;
			return m_imageBuffer + index;
		}

		Color Image::GetPixel(const GLushort &x, const GLushort &y) const
		{
			int index =  y * m_width + x;
			index *= m_bytesPerPixel;
			if (m_bytesPerPixel == 4)
			{
				return Color(m_imageBuffer[index], m_imageBuffer[index+1],
							 m_imageBuffer[index+2], m_imageBuffer[index+3]);
			}
			else if(m_bytesPerPixel == 3)
			{
				return Color(m_imageBuffer[index], m_imageBuffer[index+1],
							 m_imageBuffer[index+2], 255);
			}
			else if(m_bytesPerPixel == 2)
			{
				return Color(m_imageBuffer[index], m_imageBuffer[index],
							 m_imageBuffer[index], m_imageBuffer[index+1]);
			}
			else
			{
				return Color(m_imageBuffer[index], m_imageBuffer[index],
							 m_imageBuffer[index], 255);
			}
		}

		void Image::SetPixel(const GLushort &x, const GLushort &y, const Color &c)
		{
			int index = y * m_width + x;
			index *= m_bytesPerPixel;
			if (m_bytesPerPixel == 4)
			{
				m_imageBuffer[index] = c.r;
				m_imageBuffer[index+1] = c.g;
				m_imageBuffer[index+2] = c.b;
				m_imageBuffer[index+3] = c.a;
			}
			else if(m_bytesPerPixel == 3)
			{
				m_imageBuffer[index] = c.r;
				m_imageBuffer[index+1] = c.g;
				m_imageBuffer[index+2] = c.b;
			}
			else if(m_bytesPerPixel == 2)
			{
				unsigned char gray = (c.r + c.g + c.b) / 3;
				m_imageBuffer[index] = gray;
				m_imageBuffer[index+1] = c.a;
			}
			else
			{
				unsigned char gray = (c.r + c.g + c.b) / 3;
				m_imageBuffer[index] = gray;
			}
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

			for (int i = 0; i < rect.width; ++i)
			{
				for (int j = 0; j < rect.height; ++j)
				{
					SetPixel(point.x + i,point.y + j, image->GetPixel(rect.x + i, rect.y + j));
				}
			}
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
	}
}
