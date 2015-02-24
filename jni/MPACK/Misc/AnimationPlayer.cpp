#include "AnimationPlayer.hpp"

namespace MPACK
{
	AnimationPlayer::AnimationPlayer()
		: m_animation(0,0,1.0f), m_currentFrame(0), m_nextFrame(0), m_interpolation(0.0f)
	{
	}

	AnimationPlayer::~AnimationPlayer()
	{
	}

	void AnimationPlayer::Update(GLfloat delta)
	{
		if(m_animation.startFrame==m_animation.endFrame)
		{
			m_currentFrame=m_animation.startFrame;
			m_nextFrame=m_animation.startFrame;
			return;
		}
		if(m_animation.backward)
		{
			m_interpolation -= delta * m_animation.framesPerSecond;
			if (m_interpolation <=0.0f)
			{
				m_interpolation = 1.0f;
				--m_currentFrame;
				--m_nextFrame;
				if(m_currentFrame<m_animation.startFrame)
				{
					if(m_animation.loop)
					{
						m_currentFrame=m_animation.endFrame;
					}
					else
					{
						m_currentFrame=m_animation.startFrame;
					}
				}
				if(m_nextFrame<m_animation.startFrame)
				{
					if(m_animation.loop)
					{
						m_nextFrame=m_animation.endFrame;
					}
					else
					{

						m_nextFrame=m_animation.startFrame;
					}
				}
			}
		}
		else
		{
			m_interpolation += delta * m_animation.framesPerSecond;
			if (m_interpolation >= 1.0f)
			{
				m_currentFrame = m_nextFrame;
				m_nextFrame++;
				if (m_nextFrame > m_animation.endFrame)
				{
					if (m_animation.loop)
					{
						m_nextFrame = m_animation.startFrame;
					}
					else
					{
						m_nextFrame = m_animation.endFrame;
						m_animation.startFrame = m_animation.endFrame;
					}
				}
				m_interpolation = 0.0f;
			}
		}
	}

	void AnimationPlayer::SetAnimation(const Animation &animation)
	{
		m_animation=animation;

		m_currentFrame=m_animation.startFrame;
		m_nextFrame=m_animation.startFrame+1;
		m_interpolation=0.0f;
	}

	Animation AnimationPlayer::GetAnimation() const
	{
		return m_animation;
	}

	GLint	AnimationPlayer::GetCurrentFrame() const
	{
		return m_currentFrame;
	}

	GLint	AnimationPlayer::GetNextFrame() const
	{
		return m_nextFrame;
	}

	GLfloat	AnimationPlayer::GetInterpolation() const
	{
		return m_interpolation;
	}
}
