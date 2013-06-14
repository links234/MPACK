/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "Types.hpp"
#include "Maths.hpp"

#include <vector>

//class Texture2D;

using namespace Math;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void	UpdateVertexFormat();
	void	UpdateArrays();
//	void	MapTexCoordForAtlas(GLuint texCoord, Texture2D *texture);
	
	GLuint	GetVertexFormat();

	std::vector<Vector3f>	m_position;
	std::vector<Vector4f>	m_color;
	std::vector<Vector2f>	m_texCoord[8];
	std::vector<Vector3f>	m_normal;
	std::vector<Vector3f>	m_tangent;
protected:
	GLuint					m_vertexFormat;
};

#endif
