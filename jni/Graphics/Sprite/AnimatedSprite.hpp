#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include "Sprite.hpp"
#include "Maths.hpp"
#include "AnimationPlayer.hpp"

#include <vector>

using namespace std;
using namespace Math;

class AnimatedSprite : public Sprite, public AnimationPlayer
{
public:
	AnimatedSprite();
	virtual ~AnimatedSprite();

	void Render();

	void BuildFrameGrid(int rows, int cols);

protected:
	vector<AABB2Df> m_frames;
};

#endif
