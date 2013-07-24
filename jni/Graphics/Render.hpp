/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef RENDER_H
#define RENDER_H

#include "ShaderUniform.hpp"
#include "ShaderTypes.hpp"
#include "Vertex.hpp"
#include "TextureMappedFont.hpp"
#include "Global.hpp"

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

private:
	Render();

	static bool	s_orthoModeEnabled;
	static bool	s_needUpdateOrtho;
	static GLfloat	s_screenWidth;
    static GLfloat	s_screenHeight;
	static GLfloat	s_orthoLeft,s_orthoRight,s_orthoTop,s_orthoBottom;
	static Matrix4f	s_orthoModeMatrix;
};
#endif
