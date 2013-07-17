#ifndef PHYSICSCIRCLE_HPP
#define PHYSICSCIRCLE_HPP

#include "PMath.hpp"

#include "PShape.hpp"


namespace Core
{
	class PShape;

	class PCircle : public PShape
	{
	public:
		PCircle();
		PCircle(const PCircle& p_circle);
		PCircle(const float p_radius);

		void ComputeAABB(PAABB* p_aabb, PVec2 p_translate, float p_angle) const;

		float GetRadius() const;

		void SetRadius(float p_radius);

	private:
		float m_radius;
	};

	inline float PCircle::GetRadius() const { return m_radius; }

	inline void PCircle::SetRadius(float p_radius) { m_radius = p_radius; }
}

#endif
