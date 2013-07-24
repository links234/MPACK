/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "Render.hpp"

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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.2f,0.4f,0.4f,1.0f);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
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
		s_needUpdateOrtho=false;
		Matrix4f::SetOrtho(s_orthoModeMatrix, s_orthoLeft, s_orthoRight, s_orthoBottom, s_orthoTop, -1.0f, 1.0f);
	}
	if(!s_orthoModeEnabled)
	{
		ShaderUniform::projectionMatrix=s_orthoModeMatrix;
		glDisable(GL_DEPTH_TEST);
		s_orthoModeEnabled=true;
	}
}

void Render::DisableOrthoMode()
{
	if(s_orthoModeEnabled)
	{
		glEnable(GL_DEPTH_TEST);
		s_orthoModeEnabled=false;
	}
}

void Render::EnableAlphaBlend()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Render::DisableAlphaBlend()
{
	glDisable(GL_BLEND);
}

void Render::SetScreenSize(GLint width, GLint height)
{
	LOGD("SetScreenSize First: %d %d",width,height);

	s_needUpdateOrtho=true;
	s_screenWidth=(GLfloat)(width);
	s_screenHeight=(GLfloat)(height);

	LOGD("SetScreenSize: %f %f",s_screenWidth,s_screenHeight);

	glViewport(0,0,(GLint)(width),(GLint)(height));
}

GLint Render::GetScreenWidth()
{
	return s_screenWidth;
}

GLint Render::GetScreenHeight()
{
	return s_screenHeight;
}
