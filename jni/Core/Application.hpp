#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Types.hpp"
#include "ActivityHandler.hpp"

namespace Core
{
	class Context;
	class Texture2D;
}
namespace Game
{
	class GameState;
}

namespace Game
{
	enum
	{
		EVENT_NOTHING,
		EVENT_MAINMENU_NEWGAME,
		EVENT_MAINMENU_HIGHSCORE,
		EVENT_MAINMENU_CREDITS,
		EVENT_MAINMENU_EXIT,
		EVENT_PLAYGAME_EXIT
	};

    class Application : public Core::ActivityHandler
    {
    public:
    	Application();
    	~Application();

	protected:
        Core::Status onActivate();
        void onDeactivate();
        Core::Status onStep();

        void onStart();
        void onResume();
        void onPause();
        void onStop();
        void onDestroy();

        void onSaveState(void** pData, size_t* pSize);
        void onConfigurationChanged();
        void onLowMemory();

        void onCreateWindow();
        void onDestroyWindow();
        void onGainFocus();
        void onLostFocus();

	private:
        GameState 		*m_pGameState;
        Core::Texture2D *m_pCursorTex;
    };
}
#endif
