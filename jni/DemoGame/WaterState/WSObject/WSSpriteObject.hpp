#ifndef WSSPRITEOBJECT_HPP
#define WSSPRITEOBJECT_HPP

#include "MPACK.hpp"

#include "WSObject.hpp"

using namespace MPACK;
using namespace MPACK::Graphics;

class WSSpriteObject : virtual public WSObject
{
public:
								WSSpriteObject();
	virtual						~WSSpriteObject();

	virtual bool 				Update(float dtime);
	virtual void				Render();

	virtual void 				SetSprite(Sprite * sprite);
	virtual Vector2f 			GetCameraPosition() const;

protected:

	Sprite						*m_sprite;

};

#endif
