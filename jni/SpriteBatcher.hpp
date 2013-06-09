/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef SPRITEBATCHER_HPP
#define SPRITEBATCHER_HPP

#include "Types.hpp"
#include "Texture2D.hpp"
#include "Vertex.hpp"
#include "BufferObject.hpp"

#include <vector>

class SpriteBatcher;

using namespace Core;

class SpriteBatch
{
private:
	SpriteBatch(GLushort indexSize=0, Texture2D *texture=NULL);

	GLushort	m_indexSize;
	Texture2D	*m_texture;

	friend class SpriteBatcher;
};

class SpriteBatcher
{
public:
	static void Send(SpriteVertex *vertexPointer,GLuint vertexCount, Texture2D *texture);
	static void Send(SpriteVertex *vertexPointer,GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture);
	static void Flush();

private:
	SpriteBatcher(){}
	~SpriteBatcher(){}

	static void CompleteBatch();

	static GLushort					m_currentIndexBatchSize;
	static vector<SpriteVertex> 	m_vertexData;
	static vector<GLushort> 		m_indexData;
	static vector<SpriteBatch>		m_batches;
	static Texture2D				*m_lastTexture;
};

#endif
