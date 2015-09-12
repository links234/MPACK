#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "SpriteObject.hpp"
#include "PhysicalObject.hpp"

class Enemy : public SpriteObject, public PhysicalObject
{
public:
	Enemy(MPACK::Physics::World *world);
	virtual ~Enemy();

	virtual bool Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f GetCameraPosition() const;

private:
	MPACK::Core::VoidPointer m_thisPointer;

	MPACK::Math::Vector2f m_position;
	float m_angle;
};

#endif
