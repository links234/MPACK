#ifndef GAMERESOURCES_HPP
#define GAMERESOURCES_HPP

#include "TextureMappedFont.hpp"

namespace GameResources
{
	void InitMVFS();
	void Init();
	void Uninit();

	MPACK::Graphics::TextureMappedFont* GetFont();
}

#endif
