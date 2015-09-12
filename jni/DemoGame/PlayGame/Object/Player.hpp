#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "MPACK.hpp"

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

protected:
	MPACK::Core::VoidPointer m_thisPointer;
};

#endif
