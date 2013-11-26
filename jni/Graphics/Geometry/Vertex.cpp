/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "Vertex.hpp"

#include <sstream>

using std::ostringstream;

AbstractProgramType* Sprite_Program;

#ifdef ANDROID_PLATFORM
#define		VERTEXSHADER_SPRITE		"@Shaders/OpenGLES2/Sprite.vert"
#define		FRAGMENTSHADER_SPRITE	"@Shaders/OpenGLES2/Sprite.frag"
#elif	defined(WINDOWS_PLATFORM)
#define		VERTEXSHADER_SPRITE		"@Shaders/OpenGL2/Sprite.vert"
#define		FRAGMENTSHADER_SPRITE	"@Shaders/OpenGL2/Sprite.frag"
#elif	defined(LINUX_PLATFORM)
#define		VERTEXSHADER_SPRITE		"@Shaders/OpenGL2/Sprite.vert"
#define		FRAGMENTSHADER_SPRITE	"@Shaders/OpenGL2/Sprite.frag"
#endif

bool InitVertexPrograms()
{
	Sprite_Program = (AbstractProgramType*)(new ProgramType_Sprite(VERTEXSHADER_SPRITE,FRAGMENTSHADER_SPRITE));
	if(!Sprite_Program->Initialize())
	{
		return false;
	}
	Sprite_Program->BindAttributeLocations();
	if(!Sprite_Program->LinkProgram())
	{
		return false;
	}

	return true;
}

void DeleteVertexPrograms()
{
	delete Sprite_Program;
}
