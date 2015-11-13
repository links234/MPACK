#include "Texture2D.hpp"

#include "Image.hpp"
#include "Math.hpp"
#include "Misc.hpp"

using namespace std;

namespace MPACK
{
	namespace Graphics
	{
		GLuint	textureBinded[MAX_TEXTURES];

		Texture2D::Texture2D(bool needUpdate)
			: m_texId(0), m_sWrapMode(GL_REPEAT), m_tWrapMode(GL_REPEAT), m_filteringType(FILTER_TRILINEAR),
			  m_needUpdate(needUpdate), m_width(0), m_height(0)
		{
		}

		Texture2D::~Texture2D()
		{
			GL_CHECK( glDeleteTextures(1, &m_texId) );
		}

		bool Texture2D::Load(string path, FilteringType filtering, GLenum s_mode, GLenum t_mode)
		{
			m_path = path;
			Image *image = new Image;
			image->Load(path.c_str());
			LOGI("Texture2D::Load - path = %s",path.c_str());
			if(!image)
			{
				LOGE("Texture2D::Load - failed to load image");
				return false;
			}
			bool ret=Load((const Image*)(image),filtering,s_mode,t_mode);
			m_path = path;
			delete image;
			return ret;
		}

		bool Texture2D::Load(const Image* image, FilteringType filtering, GLenum s_mode, GLenum t_mode)
		{
			m_path = "@TEX_LOAD_IMG";

			LOGI("Texture2D::Load - load image to texture");
			GL_CHECK( glDeleteTextures(1, &m_texId) );
			GL_CHECK( glGenTextures(1, &m_texId) );
			BindTextureToSlot(m_texId,GL_TEXTURE0);

			GLenum internalFormat;
			GLenum format;
			internalFormat=format=image->GetGLFormat();

			m_width=image->GetWidth();
			m_height=image->GetHeight();
			m_filteringType=filtering;
			m_sWrapMode=s_mode;
			m_tWrapMode=t_mode;

			Init();

			GL_CHECK( glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width,
							m_height, 0, format, GL_UNSIGNED_BYTE,
							image->GetImageData()) );
			return true;
		}

		void Texture2D::Build(GLuint width, GLuint height, FilteringType filtering, GLenum s_mode, GLenum t_mode)
		{
			m_path = "@TEX_BUILD";

			GLenum colorAttachmentInternalFormat = GL_RGBA;
			GLenum colorAttachmentType = GL_UNSIGNED_BYTE;

			GL_CHECK( glDeleteTextures(1, &m_texId) );
			GL_CHECK( glGenTextures(1, &m_texId) );
			BindTextureToSlot(m_texId,GL_TEXTURE0);
			GL_CHECK( glTexImage2D(GL_TEXTURE_2D, 0, colorAttachmentInternalFormat, width, height, 0,
							 GL_RGBA, colorAttachmentType, 0) );

			m_width=width;
			m_height=height;
			m_filteringType=filtering;
			m_sWrapMode=s_mode;
			m_tWrapMode=t_mode;

			Init();
		}

		void Texture2D::Bind(GLenum TEXTURE)
		{
			BindTextureToSlot(m_texId,TEXTURE);

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
			if (m_filteringType == FILTER_POINT)
			{
				GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST) );
				GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST) );
			}
			else if (m_filteringType == FILTER_BILINEAR)
			{
				GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
				GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
			}
			else if (m_filteringType == FILTER_TRILINEAR)
			{
				GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
				GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) );
			}

			GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_sWrapMode) );
			GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_sWrapMode) );

			m_needUpdate = false;
		}

		GLuint Texture2D::GetWidth() const
		{
			return m_width;
		}

		GLuint Texture2D::GetHeight() const
		{
			return m_height;
		}

		string Texture2D::GetPath() const
		{
			return m_path;
		}

		void InitTextureSlots()
		{
			memset(textureBinded,0,sizeof(textureBinded));
		}

		void BindTextureSlot(GLenum TEXTURE)
		{
			static GLenum currentTEXTURE=0;
			if(TEXTURE!=currentTEXTURE)
			{
				GL_CHECK( glActiveTexture(TEXTURE) );
				currentTEXTURE=TEXTURE;
			}
		}

		void BindTextureToSlot(int textureId, GLenum TEXTURE)
		{
			int textureIndex=TEXTURE-GL_TEXTURE0;
			BindTextureSlot(TEXTURE);
			if(textureBinded[textureIndex]!=textureId)
			{
				textureBinded[textureIndex]=textureId;
				GL_CHECK( glBindTexture(GL_TEXTURE_2D, textureId) );
			}
		}
	}
}
