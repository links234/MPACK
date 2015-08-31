#include "Debug.hpp"

#include "TextureMappedFont.hpp"
#include "Types.hpp"
#include "Log.hpp"

using namespace std;

namespace MPACK
{
	namespace Debug
	{
		const int DEBUGMESSAGEBUFFER_SIZE = 1024;

		int		printLines = 0;
		int		circlePoints = 30;
		float	printFontSize = 40.0f;
		float	layer = 805.0f;

		void InitFrame()
		{
			printLines = 0;
		}

		void Print(Graphics::TextureMappedFont *font, const char *message, ...)
		{
			char buffer[DEBUGMESSAGEBUFFER_SIZE];
			memset(buffer,0,DEBUGMESSAGEBUFFER_SIZE);

			va_list args;
			va_start(args,message);
			vsprintf(buffer,message,args);
			va_end(args);

			GLfloat currentFontSize=font->GetFontSize();
			font->SetFontSize(printFontSize);

			font->SendString(string(buffer),5.0f,5.0f+printLines*printFontSize);

			font->SetFontSize(currentFontSize);

			++printLines;
		}

		namespace OpenGL
		{
			int	i_errorCounter = 0;
			int i_maxErrorCounter = 10;

			GLenum GetError(bool countError)
			{
				GLenum error = glGetError();
				if(error && countError)
				{
					++i_errorCounter;
					if(i_errorCounter>i_maxErrorCounter)
					{
						LOGE("OpenGL Error: Number of errors exceeded %d. Terminating process!",i_maxErrorCounter);
						terminate();
					}
				}
				return error;
			}

			void SetMaxErrorCounter(int number)
			{
				i_maxErrorCounter=number;
			}

			int GetMaxErrorCounter()
			{
				return i_maxErrorCounter;
			}

			int GetErrorCounter()
			{
				return i_errorCounter;
			}

			const char* GetErrorString(const GLenum &error)
			{
				switch(error)
				{
					case GL_NO_ERROR:
						return "GL_NO_ERROR";
					case GL_INVALID_ENUM:
						return "GL_INVALID_ENUM";
					case GL_INVALID_VALUE:
						return "GL_INVALID_VALUE";
					case GL_INVALID_OPERATION:
						return "GL_INVALID_OPERATION";
					case GL_INVALID_FRAMEBUFFER_OPERATION:
						return "GL_INVALID_FRAMEBUFFER_OPERATION";
					case GL_OUT_OF_MEMORY:
						return "GL_OUT_OF_MEMORY";
					default:
						return "UNDEFINED_ERROR";
				}
				return "UNDEFINED_ERROR";
			}

			void Assert(const char *pMessage)
			{
				GLenum error = GetError();
				if(error)
				{
					LOGE(pMessage);
					LOGE("OpenGL Error: %s",GetErrorString(error));
				}
			}

			void FlushErrors(const char *pMessage)
			{
				int errorNumber = 0;
				GLenum error = GetError();
				while(error)
				{
					++errorNumber;
					if(errorNumber == 1)
					{
						LOGE("OpenGL Error Flushing: %s",pMessage);
					}
					LOGE("Error #%d: %s",errorNumber,GetErrorString(error));
					error=GetError();
				}
			}

			void CheckErrorMacro(const char* pContent, const char* pFilename, int line)
			{
			    GLenum error = GetError();
			    if (error)
			    {
			        LOGE("OpenGL error %s (%08x), at %s:%i - for %s\n", GetErrorString(error), error, pFilename, line, pContent);
			        terminate();
			    }
			}
		}

#ifdef ANDROID_PLATFORM
		namespace EGL
		{
			int	i_errorCounter = 0;
			int i_maxErrorCounter = 1;

			EGLint GetError(bool countError)
			{
				GLenum error = eglGetError();
				if(error != EGL_SUCCESS && countError)
				{
					++i_errorCounter;
					if(i_errorCounter>i_maxErrorCounter)
					{
						LOGE("EGL Error: Number of errors exceeded %d. Terminating process!",i_maxErrorCounter);
						terminate();
					}
				}
				return error;
			}

			const char* GetErrorString(const EGLint &error)
			{
				switch(error)
				{
					case EGL_SUCCESS:
						return "EGL_SUCCESS";
					case EGL_NOT_INITIALIZED:
						return "EGL_NOT_INITIALIZED";
					case EGL_BAD_ACCESS:
						return "EGL_BAD_ACCESS";
					case EGL_BAD_ALLOC:
						return "EGL_BAD_ALLOC";
					case EGL_BAD_ATTRIBUTE:
						return "EGL_BAD_ATTRIBUTE";
					case EGL_BAD_CONTEXT:
						return "EGL_BAD_CONTEXT";
					case EGL_BAD_CONFIG:
						return "EGL_BAD_CONFIG";
					case EGL_BAD_CURRENT_SURFACE:
						return "EGL_BAD_CURRENT_SURFACE";
					case EGL_BAD_DISPLAY:
						return "EGL_BAD_DISPLAY";
					case EGL_BAD_SURFACE:
						return "EGL_BAD_SURFACE";
					case EGL_BAD_PARAMETER:
						return "EGL_BAD_PARAMETER";
					case EGL_BAD_NATIVE_PIXMAP:
						return "EGL_BAD_NATIVE_PIXMAP";
					case EGL_BAD_NATIVE_WINDOW:
						return "EGL_BAD_NATIVE_WINDOW";
					case EGL_CONTEXT_LOST:
						return "EGL_CONTEXT_LOST";
				}
				return "EGL_INVALID_ERROR";
			}

			void SetMaxErrorCounter(int number)
			{
				i_maxErrorCounter=number;
			}

			int GetMaxErrorCounter()
			{
				return i_maxErrorCounter;
			}

			int GetErrorCounter()
			{
				return i_errorCounter;
			}

			void Assert(const char *pMessage)
			{
				GLenum error = GetError();
				if(error != EGL_SUCCESS)
				{
					LOGE(pMessage);
					LOGE("EGL Error: %s",GetErrorString(error));
				}
			}

			void CheckErrorMacro(const char* pContent, const char* pFilename, int line)
			{
				GLenum error = GetError();
				if (error != EGL_SUCCESS)
				{
					LOGE("EGL error %s (%08x), at %s:%i - for %s\n", GetErrorString(error), error, pFilename, line, pContent);
					terminate();
				}
			}
		}
#endif
	}
}
