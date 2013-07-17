/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "TextureMappedFont.hpp"
#include "Render.hpp"
#include "Vertex.hpp"
#include "TargaImage.hpp"
#include "Types.hpp"

TextureMappedFont::TextureMappedFont()
	: m_layer(1000.0f), m_fontSize(40.0f), m_charSpacing(0.6f), m_monospaced(false)
{
}

void TextureMappedFont::SendString(const string& str, GLfloat x, GLfloat y, Align alignType, vector<Math::Vector4f> *colorPattern)
{
	if(alignType==ALIGN_CENTER)
	{
		GLfloat width=GetTextWidth(str);
		GLfloat height=m_fontSize;

		x-=width*0.5;
		y-=height*0.5;
	}

	GLfloat spacing(m_fontSize*m_charSpacing);

	vector<SpriteVertex> quadData;
	SpriteVertex vertex;
	vertex.stype=SpriteVertex::ALPHA_TEST;

	int ind=0;
	for(string::size_type i = 0; i < str.size(); ++i)
	{
		const GLfloat oneOverSixteen = 1.0f / 16.0f;

		GLuint ch = GLuint(str[i]);
		GLuint chX = ch / 16;
		GLuint chY = ch % 16;
		GLfloat xPos = GLfloat(ch % 16) * oneOverSixteen;
		GLfloat yPos = GLfloat(ch / 16) * oneOverSixteen;

		if(!m_monospaced)
		{
			x-=m_fontSize*m_cellSpacing[chX][chY].left;
		}

		////////////////////////////////////
		vertex.x=x;
		vertex.y=y+m_fontSize;
		vertex.s=xPos;
		vertex.t=1.0f-yPos-oneOverSixteen;
		if(!colorPattern)
		{
			vertex.r=vertex.g=vertex.b=vertex.a=1.0;
		}
		else
		{
			vertex.r=(*colorPattern)[ind].x;
			vertex.g=(*colorPattern)[ind].y;
			vertex.b=(*colorPattern)[ind].z;
			vertex.a=(*colorPattern)[ind].w;
			++ind;
			if(ind==colorPattern->size())
			{
				ind=0;
			}
		}
		quadData.push_back(vertex);

		vertex.x=x+m_fontSize;
		vertex.y=y+m_fontSize;
		vertex.s=xPos+oneOverSixteen;
		vertex.t=1.0f-yPos-oneOverSixteen;
		if(!colorPattern)
		{
			vertex.r=vertex.g=vertex.b=vertex.a=1.0;
		}
		else
		{
			vertex.r=(*colorPattern)[ind].x;
			vertex.g=(*colorPattern)[ind].y;
			vertex.b=(*colorPattern)[ind].z;
			vertex.a=(*colorPattern)[ind].w;
			++ind;
			if(ind==colorPattern->size())
			{
				ind=0;
			}
		}
		quadData.push_back(vertex);

		vertex.x=x+m_fontSize;
		vertex.y=y;
		vertex.s=xPos+oneOverSixteen;
		vertex.t=1.0f-yPos-0.001f;
		if(!colorPattern)
		{
			vertex.r=vertex.g=vertex.b=vertex.a=1.0;
		}
		else
		{
			vertex.r=(*colorPattern)[ind].x;
			vertex.g=(*colorPattern)[ind].y;
			vertex.b=(*colorPattern)[ind].z;
			vertex.a=(*colorPattern)[ind].w;
			++ind;
			if(ind==colorPattern->size())
			{
				ind=0;
			}
		}
		quadData.push_back(vertex);

		vertex.x=x;
		vertex.y=y;
		vertex.s=xPos;
		vertex.t=1.0f-yPos-0.001f;
		if(!colorPattern)
		{
			vertex.r=vertex.g=vertex.b=vertex.a=1.0;
		}
		else
		{
			vertex.r=(*colorPattern)[ind].x;
			vertex.g=(*colorPattern)[ind].y;
			vertex.b=(*colorPattern)[ind].z;
			vertex.a=(*colorPattern)[ind].w;
			++ind;
			if(ind==colorPattern->size())
			{
				ind=0;
			}
		}
		quadData.push_back(vertex);


		if(!m_monospaced)
		{
			x+=m_fontSize*(1-m_cellSpacing[chX][chY].right);
		}
		else
		{
			x+=spacing;
		}
	}

	SpriteBatcher::SendQuad(&quadData[0],quadData.size(),&m_texture,IndexData::TRIANGLES,m_layer);
}

void TextureMappedFont::SetFontSize(GLfloat fontSize)
{
	m_fontSize=fontSize;
}

void TextureMappedFont::SetCharSpacing(GLfloat charSpacing)
{
	m_charSpacing=charSpacing;
}

bool TextureMappedFont::Load(const string& textureName)
{
	TargaImage fontImage;
	if(fontImage.Load(textureName.c_str())==STATUS_KO)
	{
		LOGE("Texture Mapped Font: Could not load the font texture: %s",textureName.c_str());
		return false;
	}

	fontImage.FlipVertical();

	GLuint width=fontImage.GetWidth();
	GLuint height=fontImage.GetHeight();
	GLuint cellWidth=width>>4;
	GLuint cellHeight=height>>4;
	const float OneOver255=1.0f/255.0f;
	float OneOverCellWidth=1.0f/(GLfloat)(cellWidth);
	float OneOverCellHeight=1.0f/(GLfloat)(cellHeight);
	AABB2Df cell;
	for(register GLuint i=0;i<16;++i)
	{
		for(register GLuint j=0;j<16;++j)
		{
			cell.Clear();
			for(register GLuint ci=0;ci<cellWidth;++ci)
			{
				for(register GLuint cj=0;cj<cellHeight;++cj)
				{
					GLuint ri=i*cellWidth+ci;
					GLuint rj=j*cellHeight+cj;
					BYTE *p=(BYTE*)(fontImage.GetPixel(ri,rj));
					BYTE b=*p;
					BYTE g=*(p+1);
					BYTE r=*(p+2);
					Math::Vector3f color((GLfloat)(r)*OneOver255,(GLfloat)(g)*OneOver255,(GLfloat)(b)*OneOver255);
					if(color.Magnitude()>0.01f)
					{
						cell.AddPoint(Vector2f((GLfloat)(cj),(GLfloat)(ci)));
					}
				}
			}

			if(cell.xmin>cellWidth)
			{
				m_cellSpacing[i][j].left=OneOverCellWidth*(cellWidth>>1);
				m_cellSpacing[i][j].right=0.0f;
				m_cellSpacing[i][j].top=OneOverCellWidth*(cellWidth>>1);
				m_cellSpacing[i][j].bottom=0.0f;
			}
			else
			{
				m_cellSpacing[i][j].left=(GLfloat)(cell.xmin)*OneOverCellWidth;
				m_cellSpacing[i][j].right=(GLfloat)(cellWidth-cell.xmax)*OneOverCellWidth;
				m_cellSpacing[i][j].top=(GLfloat)(cell.ymin)*OneOverCellWidth;
				m_cellSpacing[i][j].bottom=(GLfloat)(cellHeight-cell.ymax)*OneOverCellWidth;
			}
		}
	}

	fontImage.FlipVertical();
	if (!m_texture.Load(&fontImage, Bilinear))
	{
		LOGE("Texture Mapped Font: Could not load font image to texture memory: %s",textureName.c_str());
		while(1);
		return false;
	}
	return true;

}

Texture2D* TextureMappedFont::GetTexturePointer()
{
	return &m_texture;
}

GLfloat TextureMappedFont::GetFontSize() const
{
	return m_fontSize;
}

GLfloat TextureMappedFont::GetTextWidth(const std::string &str)
{
	GLfloat width=0.0f;
	if(m_monospaced)
	{
		GLfloat spacing(m_fontSize*m_charSpacing);
		for(register int i=0;i<str.size();++i)
		{
			if(str[i]==' ')
			{
				width+=spacing;
			}
			else
			{
				width+=m_fontSize;
			}
		}
	}
	else
	{
		GLfloat x=0.0f;
		for(string::size_type i = 0; i < str.size(); ++i)
		{
			const GLfloat oneOverSixteen = 1.0f / 16.0f;

			GLuint ch = GLuint(str[i]);
			GLuint chX = ch / 16;
			GLuint chY = ch % 16;
			GLfloat xPos = GLfloat(ch % 16) * oneOverSixteen;
			GLfloat yPos = GLfloat(ch / 16) * oneOverSixteen;

			x-=m_fontSize*m_cellSpacing[chX][chY].left;

			width=x;

			x+=m_fontSize*(1-m_cellSpacing[chX][chY].right);
		}
		width+=m_fontSize;
	}
	return width;
}
