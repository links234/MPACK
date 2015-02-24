#include "Frustum.hpp"
#include "Types.hpp"

namespace MPACK
{
	namespace Math
	{
		Plane<float> Frustum::ExtractPlane(float a, float b, float c, float d)
		{
			float t = Misc<float>::Sqrt( a * a + b * b + c * c );
			Plane<float> p;
			p.a = a / t;
			p.b = b / t;
			p.c = c / t;
			p.d = d / t;
			return p;
		}

		bool Frustum::SphereInFrustum(float x, float y, float z, float radius)
		{
			for (int p = 0; p < 6; p++)
			{
				if (m_planes[p].a * x +
					m_planes[p].b * y +
					m_planes[p].c * z +
					m_planes[p].d <= -radius)
				{
					return false;
				}
			}
			return true;
		}

		bool Frustum::SphereInFrustum(Vector3f position, float radius)
		{
			for (int p = 0; p < 6; p++)
			{
				if (m_planes[p].a * position.x +
					m_planes[p].b * position.y +
					m_planes[p].c * position.z +
					m_planes[p].d <= -radius)
				{
					return false;
				}
			}
			return true;
		}

		bool Frustum::PointInFrustum( float x, float y, float z )
		{
			for (int p = 0; p < 6; p++)
			{
				if (m_planes[p].a * x +
					m_planes[p].b * y +
					m_planes[p].c * z +
					m_planes[p].d < 0)
				{
					return false;
				}
			}
			return true;
		}

		void Frustum::Update(Matrix4f *viewProjectionMatrix)
		{
			GLfloat *mvp=(GLfloat*)(viewProjectionMatrix);

			/* Extract the RIGHT plane */
			m_planes[PLANE_RIGHT] = ExtractPlane(mvp[ 3] - mvp[ 0],
												 mvp[ 7] - mvp[ 4],
												 mvp[11] - mvp[ 8],
												 mvp[15] - mvp[12]);

			/* Extract the LEFT plane */
			m_planes[PLANE_LEFT] = ExtractPlane(mvp[ 3] + mvp[ 0],
												mvp[ 7] + mvp[ 4],
												mvp[11] + mvp[ 8],
												mvp[15] + mvp[12]);

			/* Extract the TOP plane */
			m_planes[PLANE_TOP] = ExtractPlane(mvp[ 3] - mvp[ 1],
											   mvp[ 7] - mvp[ 5],
											   mvp[11] - mvp[ 9],
											   mvp[15] - mvp[13]);

			/* Extract the BOTTOM plane */
			m_planes[PLANE_BOTTOM] = ExtractPlane(mvp[ 3] + mvp[ 1],
												  mvp[ 7] + mvp[ 5],
												  mvp[11] + mvp[ 9],
												  mvp[15] + mvp[13]);

			/* Extract the FAR plane */
			m_planes[PLANE_FAR] = ExtractPlane(mvp[ 3] - mvp[ 2],
											   mvp[ 7] - mvp[ 6],
											   mvp[11] - mvp[10],
											   mvp[15] - mvp[14]);

			/* Extract the NEAR plane */
			m_planes[PLANE_NEAR] = ExtractPlane(mvp[ 3] + mvp[ 2],
											   mvp[ 7] + mvp[ 6],
											   mvp[11] + mvp[10],
											   mvp[15] + mvp[14]);
		}
	}
}
