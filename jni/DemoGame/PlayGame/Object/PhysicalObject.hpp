#ifndef PHYSICALOBJECT_HPP
#define PHYSICALOBJECT_HPP

#include "MPACK.hpp"

#include "Object.hpp"

using namespace MPACK::Core;

class PhysicalObject : virtual public Object, virtual public MPACK::Physics::PObject
{
public:
	PhysicalObject();
	virtual ~PhysicalObject();

	virtual bool Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f GetCameraPosition() const;
};

#endif
