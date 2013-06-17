#ifndef DEBUG_HPP
#define DEBUG_HPP

#define DEBUG

#ifndef DEBUG
    #define PRINT(x)
    #define D if(0)
#else
    #define PRINT(x) \
		LOGD("%s\t%s\n",#x,x)
    #define D if(1)
#endif

#include "Types.hpp"
#include "Helper.hpp"
#include "Log.hpp"

class TextureMappedFont;

namespace Debug
{
	extern GLuint	printLines;
	extern GLfloat	printFontSize;

	void InitFrame();
	void Print(TextureMappedFont *font, char *message, ...);
	void AssertGL(const char *pMessage);
}

#endif
