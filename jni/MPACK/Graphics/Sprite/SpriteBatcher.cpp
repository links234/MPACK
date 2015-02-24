/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "SpriteBatcher.hpp"

#include "Global.hpp"
#include "Render.hpp"
#include "Camera2D.hpp"
#include "Debug.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Graphics
	{
		SpriteBatch::SpriteBatch(GLushort indexSize, Texture2D *texture, IndexData::Type type)
			: m_indexSize(indexSize), m_texture(texture), m_type(type)
		{
		}

		map<GLfloat, SpriteBatcher*> 	SpriteBatcher::s_spriteBatcherLayer;
		bool							SpriteBatcher::s_useCamera=false;

		SpriteBatcher::SpriteBatcher()
			: m_currentIndexBatchSize(0), m_lastTexture(NULL), m_lastType(IndexData::NONE)
		{
		}

		void SpriteBatcher::SendDebugPolygon(Vector2f *posPointer,GLuint count,Vector4f color,TransformState2f transformState,GLfloat layer)
		{
			if(!s_spriteBatcherLayer.count(layer))
			{
				s_spriteBatcherLayer[layer]=new SpriteBatcher;
			}

			vector<SpriteVertex> vertexData;
			for(GLuint index=0;index<count;++index)
			{
				Vector2f point=posPointer[index];
				transformState.Transform(point);
				SpriteVertex vertex;
				vertex.x=point.x;
				vertex.y=point.y;
				vertex.s=vertex.t=0.0f;
				vertex.r=color.x;
				vertex.g=color.y;
				vertex.b=color.z;
				vertex.a=color.w;
				vertex.stype=SpriteVertex::NOTEXTURE;
				vertexData.push_back(vertex);
			}

			vector<GLushort> indexData;
			GLushort lastPoint=count-1;
			for(GLushort currentPoint=0;currentPoint<count;++currentPoint)
			{
				indexData.push_back(lastPoint);
				indexData.push_back(currentPoint);
				lastPoint=currentPoint;
			}

			s_spriteBatcherLayer[layer]->Send(&vertexData[0],vertexData.size(),&indexData[0],indexData.size(),NULL,IndexData::LINES);
		}

		void SpriteBatcher::SendDebugCircle(GLuint count,Vector4f color,TransformState2f transformState,GLfloat layer)
		{
			if(!s_spriteBatcherLayer.count(layer))
			{
				s_spriteBatcherLayer[layer]=new SpriteBatcher;
			}

			if(count<3)
			{
				count=3;
			}

			vector<SpriteVertex> vertexData;
			GLfloat angle=0.0f;
			GLfloat angleStep=360.0f/count;
			for(GLuint index=0;index<count;++index)
			{
				Vector2f point=Vector2f(1.0f,0.0f);
				point.Rotate(angle);
				angle+=angleStep;
				transformState.Transform(point);
				SpriteVertex vertex;
				vertex.x=point.x;
				vertex.y=point.y;
				vertex.s=vertex.t=0.0f;
				vertex.r=color.x;
				vertex.g=color.y;
				vertex.b=color.z;
				vertex.a=color.w;
				vertex.stype=SpriteVertex::NOTEXTURE;
				vertexData.push_back(vertex);
			}

			vector<GLushort> indexData;
			GLushort lastPoint=count-1;
			for(GLushort currentPoint=0;currentPoint<count;++currentPoint)
			{
				indexData.push_back(lastPoint);
				indexData.push_back(currentPoint);
				lastPoint=currentPoint;
			}

			s_spriteBatcherLayer[layer]->Send(&vertexData[0],vertexData.size(),&indexData[0],indexData.size(),NULL,IndexData::LINES);
		}

		void SpriteBatcher::SendQuad(SpriteVertex *vertexPointer,GLuint vertexCount, Texture2D *texture, IndexData::Type type, GLfloat layer)
		{
			if(!s_spriteBatcherLayer.count(layer))
			{
				s_spriteBatcherLayer[layer]=new SpriteBatcher;
			}
			s_spriteBatcherLayer[layer]->SendQuad(vertexPointer,vertexCount,texture,type);
		}

		void SpriteBatcher::Send(SpriteVertex *vertexPointer,GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, IndexData::Type type, GLfloat layer)
		{
			if(!s_spriteBatcherLayer.count(layer))
			{
				s_spriteBatcherLayer[layer]=new SpriteBatcher;
			}
			s_spriteBatcherLayer[layer]->Send(vertexPointer,vertexCount,indexPointer,indexCount,texture,type);
		}

		void SpriteBatcher::FlushAll()
		{
			for(map<GLfloat,SpriteBatcher*>::iterator it=s_spriteBatcherLayer.begin();it!=s_spriteBatcherLayer.end();++it)
			{
				(*it).second->Flush();
			}
		}

		void SpriteBatcher::EnableCamera()
		{
			s_useCamera=true;
		}

		void SpriteBatcher::DisableCamera()
		{
			s_useCamera=false;
		}

		void SpriteBatcher::SendQuad(SpriteVertex *vertexPointer,GLuint vertexCount, Texture2D *texture, IndexData::Type type)
		{
			if(vertexCount&3!=0)
			{
				LOGE("SpriteBatcher::Send quad data is corrupted");
				return;
			}

			PushMergeBatch(texture,type);
			GLushort indexOffset=m_vertexData.size();
			PushVertexData(vertexPointer,vertexCount);

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

		void SpriteBatcher::Send(SpriteVertex *vertexPointer,GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, IndexData::Type type)
		{
			PushMergeBatch(texture,type);
			GLushort indexOffset=m_vertexData.size();
			PushVertexData(vertexPointer,vertexCount);

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

			Sprite_Shader->BindShader();
			Sprite_Shader->UpdateUniforms();

			Sprite_Shader->EnableVertexAttributes();
			Sprite_Shader->SendVertexBuffer((GLfloat*)(&m_vertexData[0]));

			//LOGD("Sprite::Batcher batches = %d vertex size = %d",m_batches.size(),m_vertexData.size());

			GLuint firstVertex=0;
			GLuint firstIndex=0;
			for(vector<SpriteBatch>::iterator it=m_batches.begin();it!=m_batches.end();++it)
			{
				//LOGD("Batch index size = %d type = %d",it->m_indexSize,it->m_type);
				if(it->m_texture)
				{
					it->m_texture->Bind(GL_TEXTURE0);
				}

				glDrawElements(GetGLType(it->m_type),it->m_indexSize,GL_UNSIGNED_SHORT,&m_indexData[firstIndex]);
				Debug::AssertGL("ERROR: SpriteBatcher::Flush() : glDrawElements");

				firstIndex+=it->m_indexSize;
			}

			Sprite_Shader->DisableVertexAttributes();

			m_batches.clear();
			m_vertexData.clear();
			m_indexData.clear();
			m_lastTexture=NULL;
			m_lastType=IndexData::NONE;
		}

		void SpriteBatcher::CompleteBatch()
		{
			if(m_currentIndexBatchSize)
			{
				m_batches.push_back(SpriteBatch(m_currentIndexBatchSize,m_lastTexture,m_lastType));
				m_currentIndexBatchSize=0;
			}
		}

		void SpriteBatcher::PushMergeBatch(Texture2D *texture, IndexData::Type type)
		{
			if(!m_lastTexture)
			{
				m_lastTexture=texture;
			}

			if(m_lastType==IndexData::NONE)
			{
				m_lastType=type;
			}

			if(m_lastTexture!=texture || m_lastType!=type)
			{
				CompleteBatch();
				m_lastTexture=texture;
				m_lastType=type;
			}
		}

		void SpriteBatcher::PushVertexData(SpriteVertex *vertexPointer, GLint vertexCount)
		{
			SpriteVertex 	*vertexPointerEnd=vertexPointer+vertexCount;
			for(;vertexPointer<vertexPointerEnd;++vertexPointer)
			{
				Vector2f point(vertexPointer->x,vertexPointer->y);
				if(s_useCamera && Global::pActiveCamera)
				{
					Global::pActiveCamera->Transform(point);
				}
				SpriteVertex vertex=*vertexPointer;
				vertex.x=point.x;
				vertex.y=point.y;

				vertex.y=Render::GetScreenHeight()-vertex.y;

				m_vertexData.push_back(vertex);
			}
		}

		GLenum SpriteBatcher::GetGLType(const GLint type)
		{
			if(type==IndexData::POINTS)
			{
				return GL_POINTS;
			}
			if(type==IndexData::LINES)
			{
				return GL_LINES;
			}
			if(type==IndexData::TRIANGLES)
			{
				return GL_TRIANGLES;
			}
			return -1;
		}
	}
}
