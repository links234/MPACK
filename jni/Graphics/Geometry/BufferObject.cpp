/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "BufferObject.hpp"

template<> GLuint	BufferObject<GL_ARRAY_BUFFER>::s_currBuffer=0;
template<> GLuint	BufferObject<GL_ELEMENT_ARRAY_BUFFER>::s_currBuffer=0;
