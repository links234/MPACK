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
