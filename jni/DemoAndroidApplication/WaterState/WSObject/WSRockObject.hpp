#ifndef WSROCKOBJECT_HPP
#define WSROCKOBJECT_HPP

#include "MPACK.hpp"

#include "WSObject.hpp"
#include "WSPhysicalObject.hpp"
#include "WSSpriteObject.hpp"

using namespace MPACK;
using namespace MPACK::Graphics;
using namespace MPACK::Physics;
using namespace MPACK::Math;

class WSRockObject : public WSSpriteObject, public WSPhysicalObject
{
public:
								WSRockObject(World * m_world);
	virtual						~WSRockObject();

	virtual bool 				Update(float dtime);
	virtual void 				Render();

	virtual void 				SetSprite(Sprite * sprite);
	virtual void 				SetShape(PolygonShape * shape, Vector2f pos);

	virtual Vector2f			GetCameraPosition() const;
	virtual Body*				GetBody() const;
};

#endif
