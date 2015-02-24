#ifndef MPACK_ANIMATION_HPP
#define MPACK_ANIMATION_HPP

#include "Types.hpp"

namespace MPACK
{
	class Animation
	{
	public:
		Animation(GLuint startFrame, GLuint endFrame, GLfloat framesPerSecond=8.0f, bool loop=true, bool backward=false);

		GLint startFrame;
		GLint endFrame;
		GLfloat framesPerSecond;
		bool loop;
		bool backward;
	};
}

#endif
