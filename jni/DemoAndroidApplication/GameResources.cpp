#include "GameResources.hpp"

#include "MPACK.hpp"

using namespace std;
using namespace MPACK::Core;
using namespace MPACK::Graphics;

namespace GameResources
{
	TextureMappedFont *pFont = NULL;

	void InitMVFS()
	{
		MVFSDB::Init();
		MVFSDB::Load(0,"@Sprites.mvfs");

		vector<char> key;
		key.push_back(179);
		key.push_back(63);
		key.push_back(98);
		key.push_back(123);

		MVFSDB::Load(12,"@Shaders.mvfs",key);
	}

	void Init()
	{
		if(!pFont)
		{
			pFont = new TextureMappedFont();
			pFont->Load("@Fonts/Font.png",TextureMappedFont::ALPHA);
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

		MVFSDB::Clean();
	}

	MPACK::Graphics::TextureMappedFont* GetFont()
	{
		return pFont;
	}
}
