#include "PostEffect.hpp"

#include "ShaderTypes.hpp"

using namespace std;

namespace MPACK
{
	namespace Graphics
	{
		RenderTexture*		PostEffect::s_renderTexture1 = NULL;
		RenderTexture*		PostEffect::s_renderTexture2 = NULL;
		GLuint				PostEffect::s_screenVertexBuffer;
		GLuint				PostEffect::s_screenIndexBuffer;
		GLuint				PostEffect::s_screenIndexCount;
		GLint 				PostEffect::s_FXCount = -1;
		PostEffect*			PostEffect::s_FX[MaxFXNumber];

		PostEffect*			PostEffect::FXAAII = NULL;
		PostEffect*			PostEffect::FXAAI = NULL;

		PostEffect::PostEffect()
			: m_shader(NULL)
		{
		}

		PostEffect::PostEffect(AbstractShaderType* shader)
			: m_shader(shader)
		{
		}

		PostEffect::~PostEffect()
		{
		}

		void PostEffect::Apply()
		{
			m_shader->BindShader();
			m_shader->UpdateFrameUniforms();

			BindTextureToSlot(s_renderTexture1->m_texId,GL_TEXTURE0);

			m_shader->EnableVertexAttributes();

			GL_CHECK( glBindBuffer(GL_ARRAY_BUFFER,s_screenVertexBuffer) );
			m_shader->SendVertexBuffer();

			GL_CHECK( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,s_screenIndexBuffer) );
			GL_CHECK( glDrawElements(GL_TRIANGLES,s_screenIndexCount,GL_UNSIGNED_SHORT,BUFFER_OFFSET(0)) );

			m_shader->DisableVertexAttributes();

			GL_CHECK( glBindBuffer(GL_ARRAY_BUFFER,0) );
			GL_CHECK( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0) );
		}

		void PostEffect::Init(GLuint width, GLuint height)
		{
			ClearFX();

			vector<GLfloat> screenVertices;
			screenVertices.push_back(0.0f);
			screenVertices.push_back(0.0f);
			screenVertices.push_back(0.0f);
			screenVertices.push_back(0.0f);

			screenVertices.push_back(1.0f);
			screenVertices.push_back(0.0f);
			screenVertices.push_back(1.0f);
			screenVertices.push_back(0.0f);

			screenVertices.push_back(1.0f);
			screenVertices.push_back(1.0f);
			screenVertices.push_back(1.0f);
			screenVertices.push_back(1.0f);

			screenVertices.push_back(0.0f);
			screenVertices.push_back(1.0f);
			screenVertices.push_back(0.0f);
			screenVertices.push_back(1.0f);

			vector<GLushort> screenIndices;
			screenIndices.push_back(0);
			screenIndices.push_back(1);
			screenIndices.push_back(2);

			screenIndices.push_back(0);
			screenIndices.push_back(2);
			screenIndices.push_back(3);

			GL_CHECK( glGenBuffers(1,&s_screenVertexBuffer) );
			GL_CHECK( glBindBuffer(GL_ARRAY_BUFFER,s_screenVertexBuffer) );
			GL_CHECK( glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*screenVertices.size(),&screenVertices[0],GL_STATIC_DRAW) );
			GL_CHECK( glBindBuffer(GL_ARRAY_BUFFER,0) );

			GL_CHECK( glGenBuffers(1,&s_screenIndexBuffer) );
			GL_CHECK( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,s_screenIndexBuffer) );
			GL_CHECK( glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*screenIndices.size(),&screenIndices[0],GL_STATIC_DRAW) );
			GL_CHECK( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0) );

			s_screenIndexCount=screenIndices.size();
	
			SetScreenSize(width,height);

			FXAAII = new PostEffect(FXAAII_Shader);
			FXAAI = new PostEffect(FXAAI_Shader);
		}

		void PostEffect::SetScreenSize(GLuint width, GLuint height)
		{
			if(!s_renderTexture1)
			{
				s_renderTexture1=new RenderTexture();
			}
			if(!s_renderTexture2)
			{
				s_renderTexture2=new RenderTexture();
			}
			s_renderTexture1->Init(width,height);
			s_renderTexture2->Init(width,height);
		}

		void PostEffect::Shutdown()
		{
			if(s_renderTexture1)
			{
				delete s_renderTexture1;
				s_renderTexture1=NULL;
			}
			if(s_renderTexture2)
			{
				delete s_renderTexture2;
				s_renderTexture2=NULL;
			}
			GL_CHECK( glDeleteBuffers(1,&s_screenVertexBuffer) );
			GL_CHECK( glDeleteBuffers(1,&s_screenIndexBuffer) );

			delete FXAAII;
			FXAAII = NULL;
			delete FXAAI;
			FXAAI = NULL;
		}

		void PostEffect::Begin()
		{
			if(s_FXCount != -1)
			{
				s_renderTexture1->Bind();
			}
		}

		void PostEffect::End()
		{
			if(s_FXCount != -1)
			{
				s_renderTexture1->Unbind();
				ApplyFX();
			}
		}

		void PostEffect::PushFX(PostEffect* &FX)
		{
			s_FX[++s_FXCount]=FX;
		}
		void PostEffect::PopFX()
		{
			if(s_FXCount != -1)
			{
				--s_FXCount;
			}
		}

		void PostEffect::ClearFX()
		{
			s_FXCount=-1;
		}

		GLuint PostEffect::GetSizeFX()
		{
			return MaxFXNumber;
		}

		GLuint PostEffect::GetCountFX()
		{
			return s_FXCount+1;
		}

		void PostEffect::ApplyFX()
		{
			if(s_FXCount != -1)
			{
				Render::SetOrthoMode(0.0f,1.0f,0.0f,1.0f);
				Render::EnableOrthoMode();
				Render::DisableAlphaBlend();

				int indexFX=0;
				for(; indexFX<s_FXCount-1; ++indexFX)
				{
					s_renderTexture2->Bind();
					s_FX[indexFX]->Apply();
					std::swap(s_renderTexture1,s_renderTexture2);
				}
				s_renderTexture1->Unbind();

				s_FX[indexFX]->Apply();
			}
		}

		RenderTexture* PostEffect::GetRenderTexturePointer()
		{
			if(s_FXCount != -1)
			{
				return s_renderTexture1;
			}
			return NULL;
		}
	}
}
