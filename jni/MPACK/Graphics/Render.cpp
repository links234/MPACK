#include "Render.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Graphics
	{
		bool		Render::s_orthoModeEnabled=false;
		bool		Render::s_needUpdateOrtho=true;
		GLfloat		Render::s_screenWidth=1.0f;
		GLfloat		Render::s_screenHeight=1.0f;
		GLfloat		Render::s_orthoLeft,Render::s_orthoRight,Render::s_orthoTop,Render::s_orthoBottom;
		Matrix4f	Render::s_orthoModeMatrix;

		void Render::Init()
		{
			s_orthoModeEnabled=false;
			s_needUpdateOrtho=true;
			if(s_screenWidth==-1.0f)
			{
				s_screenWidth=s_screenHeight=1.0f;
			}

			GL_CHECK( glEnable(GL_DEPTH_TEST) );
			GL_CHECK( glDepthFunc(GL_LEQUAL) );
			GL_CHECK( glClearColor(0.2f,0.4f,0.4f,1.0f) );

			GL_CHECK( glEnable(GL_CULL_FACE) );
			GL_CHECK( glFrontFace(GL_CCW) );
			GL_CHECK( glCullFace(GL_BACK) );
		}

		void Render::Uninit()
		{
			s_screenWidth=-1.0f;
		}

		void Render::SetOrthoMode(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
		{
			if(s_orthoLeft!=left || s_orthoRight!=right || s_orthoTop!=top || s_orthoBottom!=bottom)
			{
				s_orthoLeft=left;
				s_orthoRight=right;
				s_orthoTop=top;
				s_orthoBottom=bottom;
				s_needUpdateOrtho=true;
			}
		}

		void Render::EnableOrthoMode()
		{
			if(s_needUpdateOrtho)
			{
				Matrix4f::SetOrtho(s_orthoModeMatrix, s_orthoLeft, s_orthoRight, s_orthoBottom, s_orthoTop, -1.0f, 1.0f);
			}

			if(!s_orthoModeEnabled || s_needUpdateOrtho)
			{
				ShaderUniform::projectionMatrix=s_orthoModeMatrix;
				GL_CHECK( glDisable(GL_DEPTH_TEST) );
				s_orthoModeEnabled=true;
				s_needUpdateOrtho=false;
			}
		}

		void Render::DisableOrthoMode()
		{
			if(s_orthoModeEnabled)
			{
				GL_CHECK( glEnable(GL_DEPTH_TEST) );
				s_orthoModeEnabled=false;
			}
		}

		void Render::EnableAlphaBlend()
		{
			GL_CHECK( glEnable(GL_BLEND) );
			GL_CHECK( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
		}

		void Render::DisableAlphaBlend()
		{
			GL_CHECK( glDisable(GL_BLEND) );
		}

		void Render::SetScreenSize(GLint width, GLint height)
		{
			s_needUpdateOrtho=true;
			s_screenWidth=(GLfloat)(width);
			s_screenHeight=(GLfloat)(height);

			GL_CHECK( glViewport(0,0,(GLint)(width),(GLint)(height)) );
		}

		GLint Render::GetScreenWidth()
		{
			return s_screenWidth;
		}

		GLint Render::GetScreenHeight()
		{
			return s_screenHeight;
		}

		bool Render::IsPortrait()
		{
			return s_screenWidth<s_screenHeight;
		}

		bool Render::IsLandscape()
		{
			return s_screenWidth>s_screenHeight;
		}

		AABB2Df Render::GetUISpace()
		{
			return AABB2Df(0.0f,(float)(s_screenWidth),0.0f,(float)(s_screenHeight));
		}
	}
}
