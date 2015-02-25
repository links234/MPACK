#ifndef MPACK_CAMERAOBJECT_HPP
#define MPACK_CAMERAOBJECT_HPP

#include "MPACK.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class CameraObject
		{
		public:
			CameraObject();
			virtual ~CameraObject();

			virtual Math::Vector2f GetCameraPosition() const = 0;
		};
	}
}

#endif
