#ifndef MPACK_DEBUG_HPP
#define MPACK_DEBUG_HPP

#define DEBUG

#ifndef DEBUG
    #define PRINT(x)
    #define D if(0)
#else
    #define PRINT(x) \
		LOGD("%s\t%s\n",#x,x)
    #define D if(1)
#endif

#include "Helper.hpp"
#include "Log.hpp"

#ifndef DEBUG
	#define LOGE(...)
	#define LOGW(...)
	#define LOGI(...)
	#define LOGD(...)
#else
	#define LOGE(...) MPACK::Core::Log::Error(__VA_ARGS__)
	#define LOGW(...) MPACK::Core::Log::Warn(__VA_ARGS__)
	#define LOGI(...) MPACK::Core::Log::Info(__VA_ARGS__)
	#define LOGD(...) //MPACK::Core::Log::Debug(__VA_ARGS__)
#endif

namespace MPACK
{
	namespace Graphics
	{
		class TextureMappedFont;
	}
}

namespace MPACK
{
	namespace Debug
	{
		extern int		printLines;
		extern int		circlePoints;
		extern float	printFontSize;
		extern float	layer;

		void InitFrame();
		void Print(Graphics::TextureMappedFont *font, const char *message, ...);
		void AssertGL(const char *pMessage);
	}
}

#endif
