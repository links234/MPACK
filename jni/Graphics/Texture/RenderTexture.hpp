#ifndef RENDERTEXTURE_HPP
#define RENDERTEXTURE_HPP

#include "Texture2D.hpp"

namespace Core
{
	class RenderTexture
	{
	public:
		RenderTexture();
		~RenderTexture();

		void Init(GLuint width, GLuint height);
		void Bind();
		void Unbind();

		GLuint		m_fboId;
		Texture2D	*m_colorTex;
		Texture2D	*m_depthTex;
	};
}

#endif
