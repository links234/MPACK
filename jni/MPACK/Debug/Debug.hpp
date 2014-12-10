#ifndef MPACK_DEBUG_HPP
#define MPACK_DEBUG_HPP

#define MPACK_DEBUG

#ifndef MPACK_DEBUG
    #define PRINT(x)
    #define D if(0)
#else
    #define PRINT(x) \
		LOGD("%s\t%s\n",#x,x)
    #define D if(1)
#endif

#include "Helper.hpp"
#include "Log.hpp"

class TextureMappedFont;

namespace Debug
{
	extern int		printLines;
	extern int		circlePoints;
	extern float	printFontSize;
	extern float	layer;

	void InitFrame();
	void Print(TextureMappedFont *font, const char *message, ...);
	void AssertGL(const char *pMessage);
}

#endif
