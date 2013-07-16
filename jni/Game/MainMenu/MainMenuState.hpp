#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "GameState.hpp"
#include "Texture2D.hpp"

class GUIMenu;
class Sprite;

using namespace Core;

namespace Game
{
	class MainMenu : public GameState
	{
	public:
		MainMenu();

		int Update();
		void Render();

		~MainMenu();
	private:
		GUIMenu 	*m_pMenuGUI;
		Texture2D 	*m_pButtonTexture;
		Texture2D	*m_pBackgroundTexture;
		Sprite 		*m_pButtonSprite;
		Sprite		*m_pBackgroundSprite;
	};
}

#endif
