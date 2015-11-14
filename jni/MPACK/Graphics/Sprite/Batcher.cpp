#include "Batcher.hpp"

#include "Global.hpp"
#include "Render.hpp"
#include "Camera2D.hpp"
#include "Debug.hpp"
#include "Profiler.hpp"

using namespace std;

using namespace MPACK::Core;
using namespace MPACK::Math;

namespace MPACK
{
	namespace Graphics
	{
		Batch::Batch(Type type, void *pointer)
			: m_type(type), m_pointer(pointer)
		{
		}

		Batch::~Batch()
		{
		}

		SpriteBatch::SpriteBatch(GLushort indexSize, Texture2D *texture, IndexData::Type type)
			: m_indexSize(indexSize), m_texture(texture), m_type(type)
		{
		}

		CustomRenderCall::CustomRenderCall(Param1PtrCallbackStruct callback)
			: m_callback(callback)
		{
		}

		map<GLfloat, Batcher*> 	Batcher::s_batcher;
		bool					Batcher::s_useCamera=false;

		Batcher::Batcher()
			: m_currentIndexBatchSize(0), m_lastTexture(NULL), m_lastType(IndexData::NONE)
		{
		}

		void Batcher::SendDebugPolygon(Vector2f *posPointer,GLuint count,Vector4f color,TransformState2f transformState,GLfloat layer)
		{
			if(!s_batcher.count(layer))
			{
				s_batcher[layer]=new Batcher;
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

			s_batcher[layer]->SendSpriteVertexData(&vertexData[0],vertexData.size(),&indexData[0],indexData.size(),NULL,IndexData::LINES);
		}

		void Batcher::SendDebugCircle(GLuint count,Vector4f color,TransformState2f transformState,GLfloat layer)
		{
			if(!s_batcher.count(layer))
			{
				s_batcher[layer]=new Batcher;
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

			s_batcher[layer]->SendSpriteVertexData(&vertexData[0],vertexData.size(),&indexData[0],indexData.size(),NULL,IndexData::LINES);
		}

		void Batcher::SendCustomRenderCall(Core::Param1PtrCallbackFunc func, void *param1, GLfloat layer)
		{
			if(!s_batcher.count(layer))
			{
				s_batcher[layer]=new Batcher;
			}
			s_batcher[layer]->SendCustomRenderCall(func,param1);
		}

		void Batcher::SendSpriteVertexQuad(SpriteVertex *vertexPointer,GLuint vertexCount, Texture2D *texture, IndexData::Type type, GLfloat layer)
		{
			if(!s_batcher.count(layer))
			{
				s_batcher[layer]=new Batcher;
			}
			s_batcher[layer]->SendSpriteVertexQuad(vertexPointer,vertexCount,texture,type);
		}

		void Batcher::SendSpriteVertexData(SpriteVertex *vertexPointer,GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, IndexData::Type type, GLfloat layer)
		{
			if(!s_batcher.count(layer))
			{
				s_batcher[layer]=new Batcher;
			}
			s_batcher[layer]->SendSpriteVertexData(vertexPointer,vertexCount,indexPointer,indexCount,texture,type);
		}

		void Batcher::FlushAll()
		{
			for(map<GLfloat,Batcher*>::iterator it=s_batcher.begin();it!=s_batcher.end();++it)
			{
				MPACK_DEV_PROFILE_BEGIN("Flush");
				(*it).second->Flush();
				MPACK_DEV_PROFILE_END();
			}
		}

		void Batcher::EnableCamera()
		{
			s_useCamera=true;
		}

		void Batcher::DisableCamera()
		{
			s_useCamera=false;
		}

		void Batcher::Cleanup()
		{
			for(map<GLfloat,Batcher*>::iterator it=s_batcher.begin();it!=s_batcher.end();++it)
			{
				delete (*it).second;
			}
			s_batcher.clear();
		}

		void Batcher::SendCustomRenderCall(Core::Param1PtrCallbackFunc func, void *param1)
		{
			CompleteSpriteBatch();

			m_batches.push_back(Batch(Batch::CustomRenderCall,new CustomRenderCall(Core::Param1PtrCallbackStruct(func,param1))));
		}

		void Batcher::SendSpriteVertexQuad(SpriteVertex *vertexPointer,GLuint vertexCount, Texture2D *texture, IndexData::Type type)
		{
			if(vertexCount&3!=0)
			{
				LOGE("SpriteBatcher::Send quad data is corrupted");
				return;
			}

			PushMergeSpriteBatch(texture,type);
			GLushort indexOffset=m_vertexData.size();
			PushSpriteBatchData(vertexPointer,vertexCount);

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

		void Batcher::SendSpriteVertexData(SpriteVertex *vertexPointer,GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, IndexData::Type type)
		{
			PushMergeSpriteBatch(texture,type);
			GLushort indexOffset=m_vertexData.size();
			PushSpriteBatchData(vertexPointer,vertexCount);

			GLushort		*indexPointerEnd=indexPointer+indexCount;
			for(;indexPointer<indexPointerEnd;++indexPointer)
			{
				m_indexData.push_back((*indexPointer)+indexOffset);
			}

			m_currentIndexBatchSize+=indexCount;
		}

		void Batcher::Flush()
		{
			CompleteSpriteBatch();

			bool isSpriteShaderEnabled = false;

			GLuint firstVertex=0;
			GLuint firstIndex=0;

			for(vector<Batch>::iterator it=m_batches.begin();it!=m_batches.end();++it)
			{
				if(it->m_type==Batch::SpriteBatch)
				{
					MPACK_DEV_PROFILE_BEGIN("shader bind");
					if(!isSpriteShaderEnabled)
					{
						VertexBufferObject::UnbindCurrentBuffer();
						IndexBufferObject::UnbindCurrentBuffer();

						Sprite_Shader->BindShader();
						Sprite_Shader->UpdateUniforms();

						Sprite_Shader->EnableVertexAttributes();
						Sprite_Shader->SendVertexBuffer((GLfloat*)(&m_vertexData[0]));
						isSpriteShaderEnabled = true;
					}
					MPACK_DEV_PROFILE_END();

					SpriteBatch *batch = reinterpret_cast<SpriteBatch*>(it->m_pointer);
					MPACK_DEV_PROFILE_BEGIN("tex bind");
					if(batch->m_texture)
					{
						batch->m_texture->Bind(GL_TEXTURE0);
					}
					MPACK_DEV_PROFILE_END();

					MPACK_DEV_PROFILE_BEGIN("glDrawElements");
					GL_CHECK( glDrawElements(GetGLType(batch->m_type),batch->m_indexSize,GL_UNSIGNED_SHORT,&m_indexData[firstIndex]) );
					MPACK_DEV_PROFILE_END();

					firstIndex+=batch->m_indexSize;

					delete batch;
				}
				else if(it->m_type==Batch::CustomRenderCall)
				{
					if(isSpriteShaderEnabled)
					{
						Sprite_Shader->DisableVertexAttributes();
						isSpriteShaderEnabled=false;
					}

					CustomRenderCall *batch = reinterpret_cast<CustomRenderCall*>(it->m_pointer);
					batch->m_callback.function(batch->m_callback.param1);

					delete batch;
				}
			}

			if(isSpriteShaderEnabled)
			{
				Sprite_Shader->DisableVertexAttributes();
				isSpriteShaderEnabled=false;
			}

			m_batches.clear();
			m_vertexData.clear();
			m_indexData.clear();
			m_lastTexture=NULL;
			m_lastType=IndexData::NONE;
		}

		void Batcher::CompleteSpriteBatch()
		{
			if(m_currentIndexBatchSize)
			{
				m_batches.push_back(Batch(Batch::SpriteBatch, new SpriteBatch(m_currentIndexBatchSize,m_lastTexture,m_lastType)));
				m_currentIndexBatchSize=0;
			}
		}

		void Batcher::PushMergeSpriteBatch(Texture2D *texture, IndexData::Type type)
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
				CompleteSpriteBatch();
				m_lastTexture=texture;
				m_lastType=type;
			}
		}

		void Batcher::PushSpriteBatchData(SpriteVertex *vertexPointer, GLint vertexCount)
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

		GLenum Batcher::GetGLType(const GLint type)
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
