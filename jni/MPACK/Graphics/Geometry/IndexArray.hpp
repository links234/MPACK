#ifndef MPACK_INDEXARRAY_HPP
#define MPACK_INDEXARRAY_HPP

#include <vector>

#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class MeshData;

		class IndexArray
		{
		public:
			IndexArray();
			~IndexArray();

			GLuint*	GetPointer();

			GLuint	GetSize();
	
			GLenum	GetPrimitiveType();

			void	SetPrimitiveType(GLuint primitiveType);
			void	AddIndex(GLuint index);
			void	Clear();
		protected:
			std::vector<GLuint> m_data;
			GLenum				m_primitiveType;
		};
	}
}

#endif
