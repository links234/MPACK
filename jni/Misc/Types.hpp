#ifndef TYPES_HPP
#define TYPES_HPP

#include "Platform.hpp"

#ifdef ANDROID_PLATFORM
	#include <android_native_app_glue.h>
	#include <EGL/egl.h>
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
	#include <SLES/OpenSLES.h>
	#include <SLES/OpenSLES_Android.h>
	#include <SLES/OpenSLES_AndroidConfiguration.h>
#elif defined(WINDOWS_PLATFORM)
	#include <windows.h>
	#include <map>
	#include <vector>
	#include "GLee.h"
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <cstdlib>
#include <cstring>
#include <string>

#include "Maths.hpp"
#include "../Debug/Debug.hpp"

typedef unsigned int	 	GLenum;
typedef unsigned char	 	GLboolean;
typedef unsigned int	 	GLbitfield;
typedef signed char	 	GLbyte;
typedef short			 	GLshort;
typedef int			 	GLint;
typedef int			 	GLsizei;
typedef unsigned char	 	GLubyte;
typedef unsigned short 	GLushort;
typedef unsigned int		GLuint;
typedef float				GLfloat;
typedef float				GLclampf;
typedef double				GLdouble;
typedef double				GLclampd;
typedef void				GLvoid;
typedef unsigned char		BYTE;

namespace Core
{
	typedef int		int32_t;
    typedef int32_t 	Status;

    const Status STATUS_OK   = 0;
    const Status STATUS_KO   = -1;
    const Status STATUS_EXIT = -2;

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
#endif
