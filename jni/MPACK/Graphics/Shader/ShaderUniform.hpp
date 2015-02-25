/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MPACK_SHADERUNIFORM_HPP
#define MPACK_SHADERUNIFORM_HPP

#include "Types.hpp"
#include "Math.hpp"

namespace MPACK
{
	namespace Graphics
	{
		namespace ShaderUniform
		{
			extern Math::Matrix4f		modelviewprojectionMatrix;
			extern Math::Matrix4f		modelviewMatrix;
			extern Math::Matrix4f		viewMatrix;
			extern Math::Matrix4f		projectionMatrix;
			extern GLfloat				pointSize;
		}
	}
}

#endif
