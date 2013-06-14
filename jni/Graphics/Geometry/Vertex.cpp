/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "Vertex.hpp"

#include <sstream>

using std::ostringstream;

AbstractProgramType* Sprite_Program;
AbstractProgramType* Basic2_Program;

bool InitVertexPrograms()
{
	Sprite_Program = (AbstractProgramType*)(new ProgramType_Sprite("@Sprite.vert","@Sprite.frag"));
	if(!Sprite_Program->Initialize())
	{
		return false;
	}
	Sprite_Program->BindAttributeLocations();
	if(!Sprite_Program->LinkProgram())
	{
		return false;
	}

	Basic2_Program = (AbstractProgramType*)(new ProgramType_Basic2("@basic2.vert","@basic2.frag"));
	if(!Basic2_Program->Initialize())
	{
		return false;
	}
	Basic2_Program->BindAttributeLocations();
	if(!Basic2_Program->LinkProgram())
	{
		return false;
	}

	return true;
}

void DeleteVertexPrograms()
{
	delete Sprite_Program;
	delete Basic2_Program;
}
