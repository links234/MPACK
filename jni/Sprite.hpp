/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Maths.hpp"
#include "Types.hpp"
#include "SpriteBatcher.hpp"
#include "Texture2D.hpp"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Render();
	void SetSize(GLfloat width,GLfloat height);
	void SetWidth(GLfloat width);
	void SetHeight(GLfloat height);
	void SetTexture(Texture2D *texture);

	GLfloat GetWidth();
	GLfloat GetHeight();

	GLfloat			m_rotation;
	GLfloat			m_spriteShadingType;
	Math::Vector2f	m_position;
	Math::Vector4f	m_color[4];

private:
	GLfloat			m_width,m_height;
	Texture2D		*m_texture;
};

#endif
