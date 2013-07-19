#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "PhysicalObject.hpp"
#include "SpriteObject.hpp"

using namespace Math;
using namespace Core;

class Player : public SpriteObject, public PhysicalObject
{
public:
	Player();
	virtual ~Player();

	virtual bool Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f GetCameraPosition() const;

	virtual void SetSprite(Sprite *pSprite);
};

#endif
