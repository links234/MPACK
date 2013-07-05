#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Object.hpp"

using namespace Math;

class Player : public Object
{
public:
	Player();

	void Update(GLfloat delta);
	void Render();

	~Player();
};

#endif
