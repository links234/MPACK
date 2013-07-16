#include "TiledBackground.hpp"

#include "Render.hpp"

TiledBackground::TiledBackground()
{
	SetSize(Render::GetScreenWidth()*2.0f,Render::GetScreenHeight()*2.0f);
}

TiledBackground::~TiledBackground()
{
}

void TiledBackground::Render()
{
	GLfloat Ulength=Render::GetScreenWidth()*2.0f/256.0f;
	GLfloat Vlength=Render::GetScreenHeight()*2.0f/256.0f;
	GLfloat Umin=0;
	GLfloat Umax=Umin+Ulength;
	GLfloat Vmin=0;
	GLfloat Vmax=Vmin+Vlength;
}
