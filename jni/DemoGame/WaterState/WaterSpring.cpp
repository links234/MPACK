#include "WaterSpring.hpp"
#include "WaterObject.hpp"

#include "MPACK.hpp"
#include <cmath>

using namespace MPACK;

WaterSpring::WaterSpring()
	: m_springConstant(0.50f)
	, m_springMass(2.f)
	, m_position(WaterObject::s_targetHeight)
{
	m_velocity = Vector2f(0.f, 0.f);
}

void WaterSpring::Update(float dtime)
{
	const float k = - m_springConstant / m_springMass;
	Vector2f diffHeight = m_position - WaterObject::s_targetHeight;
	Vector2f acceleration = Vector2f(0.f, diffHeight.y * k);
	acceleration -= m_velocity * WaterObject::s_dampening;

	m_position += m_velocity * dtime * 6;
	m_velocity += acceleration * dtime * 6;
}
