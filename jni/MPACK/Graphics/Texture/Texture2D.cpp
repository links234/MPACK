/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "Texture2D.hpp"

#include "TargaImage.hpp"
#include "Math.hpp"
#include "Misc.hpp"

namespace MPACK
{
	namespace Graphics
	{
		GLuint	textureBinded[MAX_TEXTURES];

		Texture2D::Texture2D()
			: m_texId(0), m_sWrapMode(GL_REPEAT), m_tWrapMode(GL_REPEAT), m_filteringType(Trilinear),
			  m_needUpdate(true), m_width(0), m_height(0)
		{
		}

		Texture2D::~Texture2D()
		{
			glDeleteTextures(1, &m_texId);
		}

		bool Texture2D::Load(string path, FilteringType filtering, GLenum s_mode, GLenum t_mode)
		{
			//REPLACE
			Image *image=LoadImage(path.c_str());
			LOGI("Texture2D::Load - path = %s",path.c_str());
			if(!image)
			{
				LOGE("Texture2D::Load - failed to load image");
				return false;
			}
			bool ret=Load((const Image*)(image),filtering,s_mode,t_mode);
			delete image;
			return ret;
		}

		bool Texture2D::Load(const Image* image, FilteringType filtering, GLenum s_mode, GLenum t_mode)
		{
			LOGI("Texture2D::Load - load image to texture");
			glDeleteTextures(1, &m_texId);
			glGenTextures(1, &m_texId);
			glBindTexture(GL_TEXTURE_2D, m_texId);

			GLenum internalFormat;
			GLenum format;
			internalFormat=format=image->GetFormat();

			m_width=image->GetWidth();
			m_height=image->GetHeight();
			m_filteringType=filtering;
			m_sWrapMode=s_mode;
			m_tWrapMode=t_mode;

			Init();

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width,
							m_height, 0, format, GL_UNSIGNED_BYTE,
							image->GetImageData());
			return true;
		}

		void Texture2D::Build(GLuint width, GLuint height, FilteringType filtering, GLenum s_mode, GLenum t_mode)
		{
			GLenum colorAttachmentInternalFormat = GL_RGBA;
			GLenum colorAttachmentType = GL_UNSIGNED_BYTE;

			glDeleteTextures(1, &m_texId);
			glGenTextures(1, &m_texId);
			glBindTexture(GL_TEXTURE_2D, m_texId);
			glTexImage2D(GL_TEXTURE_2D, 0, colorAttachmentInternalFormat, width, height, 0,
							 GL_RGBA, colorAttachmentType, 0);

			m_width=width;
			m_height=height;
			m_filteringType=filtering;
			m_sWrapMode=s_mode;
			m_tWrapMode=t_mode;

			Init();
		}

		void Texture2D::Bind(GLenum TEXTURE)
		{
			int textureIndex=TEXTURE-GL_TEXTURE0;
			BindTextureSlot(TEXTURE);
			if(textureBinded[textureIndex]!=m_texId)
			{
				textureBinded[textureIndex]=m_texId;
				glBindTexture(GL_TEXTURE_2D, m_texId);
			}

			if(m_needUpdate)
			{
				Init();
			}
		}

		void Texture2D::SetFilteringType(FilteringType filtering)
		{
			if(filtering!=m_filteringType)
			{
				m_filteringType=filtering;
				m_needUpdate=true;
			}
		}

		void Texture2D::SetWrapMode(GLenum s_mode,GLenum t_mode)
		{
			if(s_mode!=m_sWrapMode)
			{
				m_sWrapMode=s_mode;
				m_needUpdate=true;
			}
			if(t_mode!=m_tWrapMode)
			{
				m_tWrapMode=t_mode;
				m_needUpdate=true;
			}
		}

		void Texture2D::Init()
		{
			if(m_filteringType==Point)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}
			else if(m_filteringType==Bilinear)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			else if(m_filteringType==Trilinear)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_sWrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_sWrapMode);

			m_needUpdate=false;
		}

		GLuint Texture2D::GetWidth() const
		{
			return m_width;
		}

		GLuint Texture2D::GetHeight() const
		{
			return m_height;
		}

		void BindTextureSlot(GLenum TEXTURE)
		{
			static GLenum currentTEXTURE=0;
			if(TEXTURE!=currentTEXTURE)
			{
				glActiveTexture(TEXTURE);
				currentTEXTURE=TEXTURE;
			}
		}
	}
}
