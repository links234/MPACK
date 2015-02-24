#ifndef MPACK_POSTEFFECT_HPP
#define MPACK_POSTEFFECT_HPP

#include "RenderTexture.hpp"
#include "Vertex.hpp"
#include "Render.hpp"

const int MaxFXNumber=8;

namespace MPACK
{
	namespace Graphics
	{
		class PostEffect
		{
		public:
			PostEffect();
			PostEffect(AbstractShaderType* shader);
			~PostEffect();

			virtual void Apply();

			static void Init(GLuint width, GLuint height);
			static void SetScreenSize(GLuint width, GLuint height);
			static void Shutdown();

			static void Begin();
			static void End();

			static void PushFX(PostEffect* &FX);
			static void PopFX();
			static void ClearFX();
			static GLuint GetSizeFX();
			static GLuint GetCountFX();

			static PostEffect*	FXAAII;
			static PostEffect*	FXAAI;

		protected:
			static void ApplyFX();

			static RenderTexture* GetRenderTexturePointer();

			static RenderTexture *s_renderTexture1;
			static RenderTexture *s_renderTexture2;
			static GLuint s_screenVertexBuffer;
			static GLuint s_screenIndexBuffer;
			static GLuint s_screenIndexCount;

			static GLint s_FXCount;
			static PostEffect *s_FX[MaxFXNumber];

			AbstractShaderType* m_shader;
		};
	}
}

#endif
