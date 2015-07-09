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
			pFont->Load("@Fonts/Font.png",TextureMappedFont::FormatType::ALPHA);
			pFont->SetCase(TextureMappedFont::UPPERCASE);
			pFont->SetFontSize(100.0f);
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
