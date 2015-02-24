#ifndef MPACK_FRUSTUM_HPP
#define MPACK_FRUSTUM_HPP

#include "Math.hpp"

namespace MPACK
{
	namespace Math
	{
		class Frustum
		{
		public:
			void Update(Math::Matrix4f *viewProjectionMatrix);
			bool SphereInFrustum(float x, float y, float z, float radius);
			bool SphereInFrustum(Math::Vector3f position, float radius);
			bool PointInFrustum(float x, float y, float z);

		private:
			Plane<float> m_planes[6];

			enum
			{
				PLANE_LEFT = 0,
				PLANE_RIGHT,
				PLANE_TOP,
				PLANE_BOTTOM,
				PLANE_FAR,
				PLANE_NEAR
			};

			Plane<float> ExtractPlane(float a, float b, float c, float d);
		};
	}
}

#endif
