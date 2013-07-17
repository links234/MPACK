/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef SPRITEBATCHER_HPP
#define SPRITEBATCHER_HPP

#include "Types.hpp"
#include "Maths.hpp"
#include "Texture2D.hpp"
#include "Vertex.hpp"
#include "BufferObject.hpp"
#include "Debug.hpp"

#include <vector>
#include <map>

class SpriteBatcher;

using namespace Core;
using namespace Math;

namespace IndexData
{
	enum Type
	{
		NONE,
		POINTS,
		LINES,
		TRIANGLES
	};
}

class SpriteBatch
{
private:
	SpriteBatch(GLushort indexSize=0, Texture2D *texture=NULL, IndexData::Type type=IndexData::NONE);

	GLushort		m_indexSize;
	IndexData::Type	m_type;
	Texture2D		*m_texture;

	friend class SpriteBatcher;
};

class SpriteBatcher
{
public:
	static void SendDebugPolygon(Vector2f *posPointer,GLuint count,Vector4f color,TransformState2f transformState=TransformState2f(),GLfloat layer=Debug::layer);

	static void SendQuad(SpriteVertex *vertexPointer, GLuint vertexCount, Texture2D *texture, IndexData::Type type, GLfloat layer);
	static void Send(SpriteVertex *vertexPointer, GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, IndexData::Type type, GLfloat layer);
	static void FlushAll();

	static void EnableCamera();
	static void DisableCamera();

private:
	SpriteBatcher();
	~SpriteBatcher(){}

	void SendQuad(SpriteVertex *vertexPointer, GLuint vertexCount, Texture2D *texture, IndexData::Type type);
	void Send(SpriteVertex *vertexPointer, GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, IndexData::Type type);
	void Flush();

	void CompleteBatch();
	void PushMergeBatch(Texture2D *texture, IndexData::Type type);
	void PushVertexData(SpriteVertex *vertexPointer, GLint vertexCount);

	GLenum GetGLType(const GLint type);

	GLushort				m_currentIndexBatchSize;
	vector<SpriteVertex> 	m_vertexData;
	vector<GLushort> 		m_indexData;
	vector<SpriteBatch>		m_batches;
	Texture2D				*m_lastTexture;
	IndexData::Type			m_lastType;

	static map<GLfloat, SpriteBatcher*> s_spriteBatcherLayer;
	static bool						 s_useCamera;
};

#endif
