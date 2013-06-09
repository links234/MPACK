#include "Debug.hpp"
#include "Types.hpp"
#include "Log.hpp"

namespace Debug
{
	void AssertGL(const char *pMessage)
	{
		GLint error = glGetError();
		if(error)
		{
			LOGE(pMessage);
			if(error == GL_INVALID_ENUM)
			{
				LOGE("EGL Error: Invalid enum");
			}
			else if(error == GL_INVALID_VALUE)
			{
				LOGE("EGL Error: Invalid value");
			}
			else if(error == GL_INVALID_OPERATION)
			{
				LOGE("EGL Error: Invalid operation");
			}
			else
			{
				LOGE("EGL Error: Out of memory");
			}
		 }
	}
}
