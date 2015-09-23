#ifndef WSPHYSICALOBJECT_HPP
#define WSPHYSICALOBJECT_HPP

#include "MPACK.hpp"

#include "WSObject.hpp"

using namespace MPACK;
using namespace MPACK::Physics;
using namespace MPACK::Math;

class WSPhysicalObject : virtual public WSObject
{
public:
									WSPhysicalObject(World * world);
	virtual							~WSPhysicalObject();

	virtual bool					Update(float dtime);
	virtual void 					Render();

	void 							SetPosition(Vector2f pos);
	void 							SetLinearAcceleration(Vector2f force);

	virtual void 					SetShape(Shape * shape, Vector2f pos);

	virtual Vector2f				GetCameraPosition() const;
	virtual Body* 					GetBody() const;


protected:
	Shape							*m_shape;
	Body							*m_body;
	World							*m_world;
};

#endif
