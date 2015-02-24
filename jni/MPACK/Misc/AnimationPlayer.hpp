#ifndef MPACK_ANIMATIONPLAYER_HPP
#define MPACK_ANIMATIONPLAYER_HPP

#include "Animation.hpp"

namespace MPACK
{
	class AnimationPlayer
	{
	public:
		AnimationPlayer();
		virtual ~AnimationPlayer();

		virtual void 		Update(GLfloat delta);

		void 		SetAnimation(const Animation &animation);
		Animation 	GetAnimation() const;

		GLint		GetCurrentFrame() 	const;
		GLint		GetNextFrame() 		const;
		GLfloat		GetInterpolation() 	const;

	protected:
		Animation 	m_animation;

		GLint 		m_currentFrame;
		GLint 		m_nextFrame;
		GLfloat 	m_interpolation;
	};
}

#endif
