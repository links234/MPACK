/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MPACK_SHADERUNIFORM_HPP
#define MPACK_SHADERUNIFORM_HPP

#include "Types.hpp"
#include "Math.hpp"

using namespace Math;

namespace ShaderUniform
{
	extern Matrix4f				modelviewprojectionMatrix;
	extern Matrix4f				modelviewMatrix;
	extern Matrix4f				viewMatrix;
	extern Matrix4f				projectionMatrix;
	extern GLfloat				pointSize;
}

#endif
