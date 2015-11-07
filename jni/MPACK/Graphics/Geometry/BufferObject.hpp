#ifndef MPACK_BUFFEROBJECT_HPP
#define MPACK_BUFFEROBJECT_HPP

#include "Types.hpp"

#include "Debug.hpp"

namespace MPACK
{
	namespace Graphics
	{
		template<GLenum target> class BufferObject
		{
		public:
			BufferObject();
			~BufferObject();

			GLvoid Init(GLvoid *data, GLuint size, GLenum usage=GL_STATIC_DRAW);
			GLvoid Update(GLvoid *pointer, GLuint size);
			GLvoid Bind();
			GLvoid Unbind();
			GLvoid Destroy();

			GLuint GetSize();
			GLuint GetUsage();

			static GLvoid UnbindCurrentBuffer();

		private:
			GLuint	m_ibo;
			GLuint	m_size;
			GLenum	m_usage;

			static GLuint	s_currBuffer;
		};

		template<GLenum target> inline BufferObject<target>::BufferObject()
			: m_ibo(NULL), m_size(NULL), m_usage(NULL)
		{
		}

		template<GLenum target> inline BufferObject<target>::~BufferObject()
		{
			Destroy();
		}

		template<GLenum target> inline GLvoid BufferObject<target>::Init(GLvoid *data, GLuint size, GLenum usage)
		{
			Destroy();
			m_size=size;
			m_usage=usage;
			GL_CHECK( glGenBuffers(1,&m_ibo) );
			Bind();
			GL_CHECK( glBufferData(target,m_size,data,m_usage) );
		}

		template<GLenum target> inline GLvoid BufferObject<target>::Update(GLvoid *pointer, GLuint size)
		{
			if(size>m_size)
			{
				size=m_size;
			}
			Bind();
			GL_CHECK( glBufferSubData(target,0,size,pointer) );
		}

		template<GLenum target> inline GLvoid BufferObject<target>::Bind()
		{
			if(s_currBuffer!=m_ibo)
			{
				GL_CHECK( glBindBuffer(target,m_ibo) );
				s_currBuffer=m_ibo;
			}
		}

		template<GLenum target> inline GLvoid BufferObject<target>::Unbind()
		{
			if(s_currBuffer!=0)
			{
				GL_CHECK( glBindBuffer(target,0) );
				s_currBuffer=0;
			}
		}

		template<GLenum target> inline GLvoid BufferObject<target>::Destroy()
		{
			if(m_ibo)
			{
				if(s_currBuffer==m_ibo)
				{
					GL_CHECK( glBindBuffer(target,0) );
					s_currBuffer=0;
				}
				GL_CHECK( glDeleteBuffers(1,&m_ibo) );
			}
		}

		template<GLenum target> inline GLuint BufferObject<target>::GetSize()
		{
			return m_size;
		}

		template<GLenum target> inline GLenum BufferObject<target>::GetUsage()
		{
			return m_usage;
		}

		template<GLenum target> inline GLvoid BufferObject<target>::UnbindCurrentBuffer()
		{
			if(s_currBuffer!=0)
			{
				GL_CHECK( glBindBuffer(target,0) );
				s_currBuffer=0;
			}
		}

		typedef BufferObject<GL_ARRAY_BUFFER>			VertexBufferObject;
		typedef BufferObject<GL_ELEMENT_ARRAY_BUFFER>	IndexBufferObject;
	}
}

#endif
