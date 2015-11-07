#include "IndexArray.hpp"

namespace MPACK
{
	namespace Graphics
	{
		IndexArray::IndexArray()
			: m_primitiveType(0)
		{
		}

		IndexArray::~IndexArray()
		{
		}

		GLuint*	IndexArray::GetPointer()
		{
			return &m_data[0];
		}

		GLuint IndexArray::GetSize()
		{
			return (GLuint)(m_data.size());
		}

		GLenum IndexArray::GetPrimitiveType()
		{
			return m_primitiveType;
		}

		void IndexArray::SetPrimitiveType(GLuint primitiveType)
		{
			m_primitiveType=primitiveType;
		}

		void IndexArray::AddIndex(GLuint index)
		{
			m_data.push_back(index);
		}

		void IndexArray::Clear()
		{
			m_primitiveType=0;
			m_data.clear();
		}
	}
}
