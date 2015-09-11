#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "MPACK.hpp"

using namespace MPACK::Math;

#include "PhysicalObject.hpp"
#include "SpriteObject.hpp"

class Player : public SpriteObject, public PhysicalObject
{
public:
	Player(MPACK::Physics::World *world);
	virtual ~Player();

	virtual bool Update(GLfloat delta);
	virtual void Render();

	virtual MPACK::Math::Vector2f GetCameraPosition() const;

	virtual void SetSprite(MPACK::Graphics::Sprite *pSprite);

	void Shoot(MPACK::Math::Vector2f direction);
};

#endif
