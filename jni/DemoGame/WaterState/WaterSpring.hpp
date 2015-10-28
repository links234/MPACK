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
	float				m_springConstant;
	float				m_springMass;

	void 				Update(float dtime);

};


#endif
