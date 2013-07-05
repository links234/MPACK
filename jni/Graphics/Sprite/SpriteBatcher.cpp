/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "SpriteBatcher.hpp"

#include "Debug.hpp"

SpriteBatch::SpriteBatch(GLushort indexSize, Texture2D *texture)
	: m_indexSize(indexSize), m_texture(texture)
{
}

map<GLfloat, SpriteBatcher*> SpriteBatcher::s_spriteBatcherLayer;

SpriteBatcher::SpriteBatcher()
	: m_currentIndexBatchSize(0), m_lastTexture(NULL)
{
}

void SpriteBatcher::Send(SpriteVertex *vertexPointer,GLuint vertexCount, Texture2D *texture, GLfloat layer)
{
	if(!s_spriteBatcherLayer.count(layer))
	{
		s_spriteBatcherLayer[layer]=new SpriteBatcher;
	}
	s_spriteBatcherLayer[layer]->Send(vertexPointer,vertexCount,texture);
}

void SpriteBatcher::Send(SpriteVertex *vertexPointer,GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, GLfloat layer)
{
	if(!s_spriteBatcherLayer.count(layer))
	{
		s_spriteBatcherLayer[layer]=new SpriteBatcher;
	}
	s_spriteBatcherLayer[layer]->Send(vertexPointer,vertexCount,indexPointer,indexCount,texture);
}

void SpriteBatcher::FlushAll()
{
	for(map<GLfloat,SpriteBatcher*>::iterator it=s_spriteBatcherLayer.begin();it!=s_spriteBatcherLayer.end();++it)
	{
		(*it).second->Flush();
	}
}

void SpriteBatcher::Send(SpriteVertex *vertexPointer,GLuint vertexCount, Texture2D *texture)
{
	if(vertexCount&3!=0)
	{
		LOGE("SpriteBatcher::Send quad data is corrupted");
		return;
	}

	if(!m_lastTexture)
	{
		m_lastTexture=texture;
	}

	if(texture!=m_lastTexture)
	{
		CompleteBatch();
		m_lastTexture=texture;
	}

	GLushort indexOffset=m_vertexData.size();

	SpriteVertex 	*vertexPointerEnd=vertexPointer+vertexCount;
	for(;vertexPointer<vertexPointerEnd;++vertexPointer)
	{
		m_vertexData.push_back(*vertexPointer);
	}

	GLushort quadIndex[]={ 	0,1,2,
							2,3,0 };

	GLushort quadCount=vertexCount>>2;
	for(GLushort quad=0;quad<quadCount;++quad)
	{
		for(GLushort i=0;i<6;++i)
		{
			m_indexData.push_back(indexOffset+quad*4+quadIndex[i]);
		}
	}

	m_currentIndexBatchSize+=quadCount*6;
}

void SpriteBatcher::Send(SpriteVertex *vertexPointer,GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture)
{
	if(!m_lastTexture)
	{
		m_lastTexture=texture;
	}

	if(texture!=m_lastTexture)
	{
		CompleteBatch();
		m_lastTexture=texture;
	}

	GLushort indexOffset=m_vertexData.size();

	SpriteVertex 	*vertexPointerEnd=vertexPointer+vertexCount;
	for(;vertexPointer<vertexPointerEnd;++vertexPointer)
	{
		m_vertexData.push_back(*vertexPointer);
	}

	GLushort		*indexPointerEnd=indexPointer+indexCount;
	for(;indexPointer<indexPointerEnd;++indexPointer)
	{
		m_indexData.push_back((*indexPointer)+indexOffset);
	}

	m_currentIndexBatchSize+=indexCount;
}

void SpriteBatcher::Flush()
{
	CompleteBatch();

	VertexBufferObject::UnbindCurrentBuffer();
	IndexBufferObject::UnbindCurrentBuffer();

	Sprite_Program->BindShader();
	Sprite_Program->UpdateUniforms();

	Sprite_Program->EnableVertexAttributes();
	Sprite_Program->SendVertexBuffer((GLfloat*)(&m_vertexData[0]));

	//LOGD("Sprite::Batcher batches = %d",m_batches.size());

	GLuint firstVertex=0;
	GLuint firstIndex=0;
	for(vector<SpriteBatch>::iterator it=m_batches.begin();it!=m_batches.end();++it)
	{
		//LOGD("Batch index size = %d",it->m_indexSize);

		it->m_texture->Bind(GL_TEXTURE0);
		glDrawElements(GL_TRIANGLES,it->m_indexSize,GL_UNSIGNED_SHORT,&m_indexData[firstIndex]);

		firstIndex+=it->m_indexSize;
	}

	Sprite_Program->DisableVertexAttributes();

	m_batches.clear();
	m_vertexData.clear();
	m_indexData.clear();
	m_lastTexture=NULL;
}

void SpriteBatcher::CompleteBatch()
{
	if(m_currentIndexBatchSize)
	{
		m_batches.push_back(SpriteBatch(m_currentIndexBatchSize,m_lastTexture));
		m_currentIndexBatchSize=0;
	}
}
