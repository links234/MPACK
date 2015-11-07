#ifndef MPACK_BATCHER_HPP
#define MPACK_BATCHER_HPP

#include "Types.hpp"
#include "Math.hpp"
#include "Texture2D.hpp"
#include "Vertex.hpp"
#include "BufferObject.hpp"
#include "Debug.hpp"

#include <vector>
#include <map>

namespace MPACK
{
	namespace Graphics
	{
		class Batcher;
	}
}

namespace MPACK
{
	namespace Graphics
	{
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

		class SpriteBatch;
		class CustomRenderCall;

		class Batch
		{
		public:
			~Batch();

		private:
			enum Type {SpriteBatch, CustomRenderCall};

			Batch(Type type, void *pointer);

			Type m_type;
			void *m_pointer;

			friend class Batcher;
		};

		class SpriteBatch
		{
		private:
			SpriteBatch(GLushort indexSize=0, Texture2D *texture=NULL, IndexData::Type type=IndexData::NONE);

			GLushort		m_indexSize;
			IndexData::Type	m_type;
			Texture2D		*m_texture;

			friend class Batcher;
			friend class Batch;
		};

		class CustomRenderCall
		{
		private:
			CustomRenderCall(Core::Param1PtrCallbackStruct callback);

			Core::Param1PtrCallbackStruct m_callback;

			friend class Batcher;
			friend class Batch;
		};

		class Batcher
		{
		public:
			static void SendDebugPolygon(Math::Vector2f *posPointer,GLuint count,Math::Vector4f color,Math::TransformState2f transformState=Math::TransformState2f(),GLfloat layer=Debug::layer);
			static void SendDebugCircle(GLuint count,Math::Vector4f color,Math::TransformState2f transformState=Math::TransformState2f(),GLfloat layer=Debug::layer);

			static void SendCustomRenderCall(Core::Param1PtrCallbackFunc func, void *param1, GLfloat layer);

			static void SendSpriteVertexQuad(SpriteVertex *vertexPointer, GLuint vertexCount, Texture2D *texture, IndexData::Type type, GLfloat layer);
			static void SendSpriteVertexData(SpriteVertex *vertexPointer, GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, IndexData::Type type, GLfloat layer);
			static void FlushAll();

			static void EnableCamera();
			static void DisableCamera();

			static void Cleanup();

		private:
			Batcher();
			~Batcher(){}

			void SendCustomRenderCall(Core::Param1PtrCallbackFunc func, void *param1);

			void SendSpriteVertexQuad(SpriteVertex *vertexPointer, GLuint vertexCount, Texture2D *texture, IndexData::Type type);
			void SendSpriteVertexData(SpriteVertex *vertexPointer, GLuint vertexCount, GLushort *indexPointer, GLushort indexCount, Texture2D *texture, IndexData::Type type);
			void Flush();

			void CompleteSpriteBatch();
			void PushMergeSpriteBatch(Texture2D *texture, IndexData::Type type);
			void PushSpriteBatchData(SpriteVertex *vertexPointer, GLint vertexCount);

			GLenum GetGLType(const GLint type);

			GLushort					m_currentIndexBatchSize;
			std::vector<SpriteVertex> 	m_vertexData;
			std::vector<GLushort> 		m_indexData;
			std::vector<Batch>			m_batches;
			Texture2D					*m_lastTexture;
			IndexData::Type				m_lastType;

			static std::map<GLfloat, Batcher*> 	s_batcher;
			static bool				 			s_useCamera;
		};
	}
}

#endif
