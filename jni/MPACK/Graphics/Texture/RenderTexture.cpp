#include "RenderTexture.hpp"

namespace MPACK
{
	namespace Graphics
	{
		RenderTexture::RenderTexture()
			: m_fboId(0), m_depthTex(NULL), m_colorTex(NULL)
		{
		}
		RenderTexture::~RenderTexture()
		{
			glDeleteFramebuffers(1,&m_fboId);
			if(m_colorTex)
			{
				delete m_colorTex;
				m_colorTex = NULL;
			}
			if(m_depthTex)
			{
				delete m_depthTex;
				m_depthTex = NULL;
			}
		}
		void RenderTexture::Init(GLuint width, GLuint height)
		{
			glDeleteFramebuffers(1,&m_fboId);
			if(m_colorTex)
			{
				glDeleteTextures(1,&m_colorTex->m_texId);
			}
			else
			{
				m_colorTex=new Texture2D();
			}
			glGenTextures(1, &m_colorTex->m_texId);
			glBindTexture(GL_TEXTURE_2D, m_colorTex->m_texId);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
						 GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

			if(m_depthTex)
			{
				glDeleteTextures(1,&m_depthTex->m_texId);
			}
			else
			{
				m_depthTex=new Texture2D();
			}
			glGenTextures(1, &m_depthTex->m_texId);
			glBindTexture(GL_TEXTURE_2D, m_depthTex->m_texId);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0,
						 GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
			glBindTexture(GL_TEXTURE_2D, 0);

			glGenFramebuffers(1, &m_fboId);
			glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
									  GL_TEXTURE_2D, m_colorTex->m_texId, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
									  GL_TEXTURE_2D, m_depthTex->m_texId, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if ( status == GL_FRAMEBUFFER_COMPLETE )
			{
				LOGI("FBO successfully created!");
			}
			else
			{
				LOGE("ERROR: Failed to init FBO");
			}
		}
		void RenderTexture::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
		}
		void RenderTexture::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}
