#ifndef WATERSPRING_HPP
#define WATERSPRING_HPP

#include "MPACK.hpp"

using namespace MPACK;
using namespace MPACK::Math;

class WaterSpring
{
public:
						WaterSpring();
	Vector2f			m_position;
	Vector2f			m_velocity;
	const float			m_springConstant;
	const float			m_springMass;
	const float			m_dampening;

	void 				Update(float dtime);

};


#endif
