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
#include <map>

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
	static void Send(SpriteVertex *vertexPointer,GLuint vertexCount, Texture2D *texture, GLfloat layer);
	static void Send(SpriteVertex *vertexPointer,GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, GLfloat layer);
	static void FlushAll();

	static void EnableCamera();
	static void DisableCamera();

private:
	SpriteBatcher();
	~SpriteBatcher(){}

	void Send(SpriteVertex *vertexPointer,GLuint vertexCount, Texture2D *texture);
	void Send(SpriteVertex *vertexPointer,GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture);
	void Flush();

	void CompleteBatch();
	void PushVertexData(SpriteVertex *vertexPointer, GLint vertexCount);

	GLushort				m_currentIndexBatchSize;
	vector<SpriteVertex> 	m_vertexData;
	vector<GLushort> 		m_indexData;
	vector<SpriteBatch>		m_batches;
	Texture2D				*m_lastTexture;

	static map<GLfloat, SpriteBatcher*> s_spriteBatcherLayer;
	static bool						 s_useCamera;
};

#endif
