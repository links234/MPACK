#ifndef MPACK_ANIMATEDSPRITE_HPP
#define MPACK_ANIMATEDSPRITE_HPP

#include "Sprite.hpp"
#include "Math.hpp"
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
