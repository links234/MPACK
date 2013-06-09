/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "IndexArray.hpp"

IndexArray::IndexArray()
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
