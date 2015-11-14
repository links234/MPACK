#ifndef MPACK_DEBUG_HPP
#define MPACK_DEBUG_HPP

#define DEBUG
#define PROFILE

//#define MPACK_DEV_DEBUG
//#define MPACK_DEV_PROFILE

#include "Types.hpp"
#include "Profiler.hpp"
#include "Helper.hpp"
#include "Log.hpp"

#ifndef DEBUG
    #define PRINT(x)
    #define D if(0)
#else
    #define PRINT(x) \
		LOGD("%s\t = %s\n",#x,x)
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

#ifndef PROFILE
	#define PROFILE_BEGIN(x)
	#define PROFILE_END()
	#define PROFILE_PRINT()
	#define PROFILE_STEP()
#else
	#define PROFILE_BEGIN(x) 	do { \
			MPACK::Profiler::Begin(x); \
		} while(0)
	#define PROFILE_END()		do { \
			MPACK::Profiler::End(); \
		} while(0)
	#define PROFILE_PRINT()	\
		vector< pair<string, double> > sortedData = MPACK::Profiler::GetTime(); \
		float prevFontSize = Global::pFont->GetFontSize(); \
		MPACK::Global::pFont->SetFontSize(5.0f); \
		\
		for(vector< pair<string, double> >::iterator it=sortedData.begin();it!=sortedData.end();++it) \
		{ \
			MPACK::Debug::Print(Global::pFont,"%s = %.0lf us",it->first.c_str(),it->second*1000.0*1000.0); \
		} \
		\
		MPACK::Global::pFont->SetFontSize(prevFontSize);
	#define PROFILE_STEP()		do { \
			MPACK::Profiler::Step(); \
		} while(0)
#endif

#ifndef MPACK_DEV_PROFILE
	#define MPACK_DEV_PROFILE_BEGIN(x)
	#define MPACK_DEV_PROFILE_END()
#else
	#define MPACK_DEV_PROFILE_BEGIN(x) 	PROFILE_BEGIN(x)
	#define MPACK_DEV_PROFILE_END()		PROFILE_END()
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
