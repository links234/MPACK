#ifndef MPACK_RENDER_H
#define MPACK_RENDER_H

#include "ShaderUniform.hpp"
#include "ShaderTypes.hpp"
#include "Vertex.hpp"
#include "TextureMappedFont.hpp"
#include "Global.hpp"
#include "Math.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Render
		{
		public:
			static void Init();
			static void Uninit();
			static void SetOrthoMode(GLfloat left=0.0f, GLfloat right=s_screenWidth, GLfloat bottom=0.0f, GLfloat top=s_screenHeight);
			static void EnableOrthoMode();
			static void DisableOrthoMode();
			static void EnableAlphaBlend();
			static void DisableAlphaBlend();
			static void SetScreenSize(GLint width, GLint height);

			static bool IsOrthoModeEnabled();

			static GLint GetScreenWidth();
			static GLint GetScreenHeight();

			static bool IsPortrait();
			static bool IsLandscape();

			static Math::AABB2Df GetUISpace();

		private:
			Render();

			static bool	s_orthoModeEnabled;
			static bool	s_needUpdateOrtho;
			static GLfloat	s_screenWidth;
			static GLfloat	s_screenHeight;
			static GLfloat	s_orthoLeft,s_orthoRight,s_orthoTop,s_orthoBottom;
			static Math::Matrix4f	s_orthoModeMatrix;
		};
	}
}

#endif
