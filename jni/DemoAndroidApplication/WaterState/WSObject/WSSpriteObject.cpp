#include "WSSpriteObject.hpp"
#include <cassert>

using namespace MPACK;
using namespace MPACK::Graphics;

WSSpriteObject::WSSpriteObject()
{
}

WSSpriteObject::~WSSpriteObject()
{
	delete m_sprite;
}

bool WSSpriteObject::Update(float dtime)
{
	// stuff to do ?!
	return true;
}

void WSSpriteObject::Render()
{
	assert(m_sprite);
	m_sprite->Render();
}

void WSSpriteObject::SetSprite(Sprite * sprite)
{
	assert(sprite);
	m_sprite = sprite;
}

Vector2f WSSpriteObject::GetCameraPosition() const
{
	return m_sprite->m_position;
}
