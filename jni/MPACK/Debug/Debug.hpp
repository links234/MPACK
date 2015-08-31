#ifndef MPACK_DEBUG_HPP
#define MPACK_DEBUG_HPP

#define DEBUG

#include "Types.hpp"
#include "Helper.hpp"
#include "Log.hpp"

#ifndef DEBUG
    #define PRINT(x)
    #define D if(0)
#else
    #define PRINT(x) \
		LOGD("%s\t%s\n",#x,x)
    #define D if(1)
#endif

#ifndef DEBUG
	#define LOGE(...)
	#define LOGW(...)
	#define LOGI(...)
	#define LOGD(...)
#else
	#define LOGE(...) MPACK::Core::Log::Error(__VA_ARGS__)
	#define LOGW(...) MPACK::Core::Log::Warn(__VA_ARGS__)
	#define LOGI(...) MPACK::Core::Log::Info(__VA_ARGS__)
	#define LOGD(...) MPACK::Core::Log::Debug(__VA_ARGS__)
#endif

#ifndef DEBUG
	#define GL_CHECK(something) something
#else
	#define GL_CHECK(something) do { \
            something; \
            MPACK::Debug::OpenGL::CheckErrorMacro(#something, __FILE__, __LINE__); \
        } while (0)
#endif

#ifndef DEBUG
	#define EGL_CHECK(something) something
#else
	#define EGL_CHECK(something) do { \
            something; \
            MPACK::Debug::EGL::CheckErrorMacro(#something, __FILE__, __LINE__); \
        } while (0)
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

		namespace OpenGL
		{
			GLenum GetError(bool countError = true);
			const char* GetErrorString(const GLenum &error);

			void SetMaxErrorCounter(int number);
			int GetMaxErrorCounter();

			int GetErrorCounter();

			void Assert(const char *pMessage);
			void FlushErrors(const char *pMessage);

			void CheckErrorMacro(const char* pContent, const char* pFilename, int line);
		}

#ifdef ANDROID_PLATFORM
		namespace EGL
		{
			EGLint GetError(bool countError = true);
			const char* GetErrorString(const EGLint &error);

			void SetMaxErrorCounter(int number);
			int GetMaxErrorCounter();

			int GetErrorCounter();

			void Assert(const char *pMessage);

			void CheckErrorMacro(const char* pContent, const char* pFilename, int line);
		}
#endif
	}
}

#endif
