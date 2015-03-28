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

			GLenum GetError()
			{
				GLenum error = glGetError();
				if(error)
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
	}
}
