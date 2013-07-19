#ifndef PHYSICALOBJECT_HPP
#define PHYSICALOBJECT_HPP

#include "Object.hpp"
#include "PObject.hpp"

using namespace Core;

class PhysicalObject : virtual public Object, virtual public PObject
{
public:
	PhysicalObject();
	virtual ~PhysicalObject();

	virtual bool Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f GetCameraPosition() const;
};

#endif
