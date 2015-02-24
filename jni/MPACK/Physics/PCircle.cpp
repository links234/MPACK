#include "PCircle.hpp"

namespace MPACK
{
	namespace Physics
	{
		PCircle::PCircle()
		{
			m_type = e_circle;
			m_radius = 0.5f;

		}

		PCircle::PCircle(const PCircle& p_circle)
		{
			m_type = e_circle;

			m_radius = p_circle.GetRadius();
		}

		PCircle::PCircle(float p_radius)
		{
			m_type = e_circle;

			m_radius = p_radius;
		}
		void PCircle::ComputeAABB(PAABB* p_aabb, PVec2 p_translate, float p_angle) const
		{
			*p_aabb = PAABB();

			p_aabb->AddPoint(PVec2(-m_radius, -m_radius));
			p_aabb->AddPoint(PVec2(m_radius, m_radius));


			p_aabb->m_xmin += p_translate.x;
			p_aabb->m_xmax += p_translate.x;

			p_aabb->m_ymin += p_translate.y;
			p_aabb->m_ymax += p_translate.y;
		}
	}
}
