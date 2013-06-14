/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef TEXTUREMAPPEDFONT_H
#define TEXTUREMAPPEDFONT_H

#include "Texture2D.hpp"
#include "Vertex.hpp"
#include "Debug.hpp"
#include "Maths.hpp"
#include "Sprite.hpp"

#include <vector>
#include <string>

using std::vector;
using std::string;

struct CellSpacing
{
	GLfloat top,bottom,left,right;
};

enum Align
{
	ALIGN_LEFT_TOP,
	ALIGN_CENTER
};

class TextureMappedFont
{
public:
    TextureMappedFont();

	void SetFontSize(GLfloat fontSize);
	void SetCharSpacing(GLfloat charSpacing=0.0f);
	void SetMonospaced(bool monospaced=true);
    void SendString(const std::string& str, GLfloat x, GLfloat y, Align alignType=ALIGN_LEFT_TOP, vector<Math::Vector4f> *colorPattern=NULL);

    bool Load(const string& textureName);

	Texture2D* GetTexturePointer();

	GLfloat GetTextWidth(const std::string &str);

private:
    Texture2D		m_texture;

	GLfloat			m_fontSize;
	GLfloat			m_charSpacing;
	bool			m_monospaced;

	CellSpacing		m_cellSpacing[16][16];
};

#endif
