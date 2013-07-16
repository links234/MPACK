#ifndef TILEDBACKGROUND_HPP
#define TILEDBACKGROUND_HPP

#include "Sprite.hpp"

class TiledBackground: public Sprite
{
public:
	TiledBackground();
	virtual ~TiledBackground();

	virtual void Render();
};

#endif
