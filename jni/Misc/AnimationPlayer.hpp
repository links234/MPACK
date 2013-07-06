#ifndef ANIMATIONPLAYER_HPP
#define ANIMATIONPLAYER_HPP

#include "Animation.hpp"

class AnimationPlayer
{
public:
	void 		Update(GLfloat delta);

	void 		SetAnimation(const Animation &animation);
	Animation 	GetAnimation() const;

	GLint		GetCurrentFrame() 	const;
	GLint		GetNextFrame() 		const;
	GLfloat		GetInterpolation() 	const;

private:
	Animation 	m_animation;

	GLint 		m_currentFrame;
	GLint 		m_nextFrame;
	GLfloat 	m_interpolation;
};

#endif
