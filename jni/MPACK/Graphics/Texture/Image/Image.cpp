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
	}
}
