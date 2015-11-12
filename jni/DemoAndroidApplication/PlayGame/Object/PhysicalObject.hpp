#ifndef PHYSICALOBJECT_HPP
#define PHYSICALOBJECT_HPP

#include "MPACK.hpp"

#include "Object.hpp"

using namespace MPACK::Core;

class PhysicalObject : virtual public Object
{
public:
	PhysicalObject(MPACK::Physics::World *world);
	virtual ~PhysicalObject();

	virtual bool Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f GetCameraPosition() const;

	void SetPosition(Vector2f pos);
	void SetLinearAcceleration(Vector2f force);

	bool inCollision;

protected:
	MPACK::Physics::Shape *m_shape;
	MPACK::Physics::Body *m_body;
	MPACK::Physics::World *m_world;
};

#endif
