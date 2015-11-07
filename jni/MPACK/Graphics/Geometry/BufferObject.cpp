#include "BufferObject.hpp"

namespace MPACK
{
	namespace Graphics
	{
		template<> GLuint	BufferObject<GL_ARRAY_BUFFER>::s_currBuffer=0;
		template<> GLuint	BufferObject<GL_ELEMENT_ARRAY_BUFFER>::s_currBuffer=0;
	}
}
