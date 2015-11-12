#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "MPACK.hpp"

using namespace MPACK::Core;

#include "GameState.hpp"

class GUIMenu;

namespace Demo
{
	class MainMenu : public GameState
	{
	public:
		MainMenu(bool isGamePaused=false);

		int Update();
		void Render();

		void Pause();
		void Continue();

		~MainMenu();
	private:
		GUIMenu 					*m_pMenuGUI;
		MPACK::Graphics::Texture2D 	*m_pButtonTexture;
		MPACK::Graphics::Texture2D	*m_pBackgroundTexture;
		MPACK::Graphics::Sprite 	*m_pButtonSprite;
		MPACK::Graphics::Sprite		*m_pBackgroundSprite;
	};
}

#endif
