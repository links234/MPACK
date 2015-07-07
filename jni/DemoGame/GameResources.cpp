#include "GameResources.hpp"

using namespace MPACK::Graphics;

namespace GameResources
{
	TextureMappedFont *pFont = NULL;

	void Init()
	{
		if(!pFont)
		{
			pFont = new TextureMappedFont();
			pFont->Load("@Fonts/Font.png");
			pFont->SetCase(TextureMappedFont::UPPERCASE);
		}
	}

	void Uninit()
	{
		if(pFont)
		{
			delete pFont;
			pFont = NULL;
		}
	}

	MPACK::Graphics::TextureMappedFont* GetFont()
	{
		return pFont;
	}
}
