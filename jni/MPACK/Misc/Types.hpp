#ifndef TYPES_HPP
#define TYPES_HPP

#ifdef ANDROID_PLATFORM
	#include <android_native_app_glue.h>
	#include <EGL/egl.h>
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
	#include <SLES/OpenSLES.h>
	#include <SLES/OpenSLES_Android.h>
	#include <SLES/OpenSLES_AndroidConfiguration.h>
#elif	defined(WINDOWS_PLATFORM)
	#include <windows.h>
	#include "GLee.h"
	#include <GL/gl.h>
	#include <GL/glu.h>
#elif	defined(LINUX_PLATFORM)
	#define GLX_GLXEXT_LEGACY
	#include "GLee.h"
	#include <GL/glx.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "glxext.h"
	#include <cstdarg>
	#include <cstdio>
	#include <time.h>
#endif

#ifdef LINUX_PLATFORM
	#include <stdint.h>

	typedef int		EGLint;
#elif	defined(ANDROID_PLATFORM)
	//#define	intptr_t int
#elif	defined(WINDOWS_PLATFORM)
	#define nullptr NULL
	#define unordered_map map
	#define unordered_set set
#endif



#include <cstdlib>
#include <cstring>

#include <iostream>
#include <fstream>

#include <exception>

#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>

#if defined(LINUX_PLATFORM) || defined(ANDROID_PLATFORM)
	#include <unordered_map>
	#include <unordered_set>
#endif

#include "Math.hpp"
#include "Uncopyable.hpp"
#include "../Debug/Debug.hpp"

typedef unsigned int	 	GLenum;
typedef unsigned char	 	GLboolean;
typedef unsigned int	 	GLbitfield;
typedef signed char	 		GLbyte;
typedef short			 	GLshort;
typedef int			 		GLint;
typedef int			 		GLsizei;
typedef unsigned char	 	GLubyte;
typedef unsigned short 		GLushort;
typedef unsigned int		GLuint;
typedef float				GLfloat;
typedef float				GLclampf;
typedef double				GLdouble;
typedef double				GLclampd;
typedef void				GLvoid;
typedef unsigned char		BYTE;

namespace MPACK
{
	namespace Core
	{
		typedef int		int32_t;
		typedef int32_t	 	ReturnValue;

		const ReturnValue RETURN_VALUE_OK   = 0;
		const ReturnValue RETURN_VALUE_KO   = -1;
		const ReturnValue RETURN_VALUE_EXIT = -2;

		typedef void (*Param0CallbackFunc)();
		typedef void (*Param1PtrCallbackFunc)(void*);
		typedef void (*Param2PtrCallbackFunc)(void*, void*);

		struct Param1PtrCallbackStruct
		{
			Param1PtrCallbackStruct(Param1PtrCallbackFunc function, void *param1)
				:	function(function), param1(param1)
			{
			}

			Param1PtrCallbackFunc function;
			void *param1;

			bool operator== (const Param1PtrCallbackStruct &other)
			{
				if(function!=other.function)
					return false;
				if(param1!=other.param1)
					return false;
				return true;
			}
		};

		struct Param2PtrCallbackStruct
		{
			Param2PtrCallbackStruct(Param2PtrCallbackFunc function, void *param1)
				:	function(function), param1(param1)
			{
			}

			Param2PtrCallbackFunc function;
			void *param1;

			bool operator== (const Param2PtrCallbackStruct &other)
			{
				if(function!=other.function)
					return false;
				if(param1!=other.param1)
					return false;
				return true;
			}
		};
	}
}

#endif
