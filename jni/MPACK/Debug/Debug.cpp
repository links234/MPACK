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

		int		printLines;
		int		circlePoints = 30;
		float	printFontSize = 40.0f;
		float	layer = 805.0f;

		void InitFrame()
		{
			printLines=0;
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
}
