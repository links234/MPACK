#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Types.hpp"
#include "ActivityHandler.hpp"



namespace MPACK
{
	namespace Core
	{
		class Context;
	}
	namespace Graphics
	{
		class Texture2D;
	}
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
		EVENT_MAINMENU_CONTINUE,
		EVENT_MAINMENU_NEWGAME,
		EVENT_MAINMENU_HIGHSCORE,
		EVENT_MAINMENU_CREDITS,
		EVENT_MAINMENU_EXIT,
		EVENT_PLAYGAME_PAUSE,
		EVENT_PLAYGAME_EXIT
	};

    class Application : public MPACK::Core::ActivityHandler
    {
    public:
    	Application();
    	~Application();

	protected:
        MPACK::Core::ReturnValue onActivate();
        void onDeactivate();
        MPACK::Core::ReturnValue onStep();

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
        GameState		*m_pSavedGameState;
        MPACK::Graphics::Texture2D *m_pCursorTex;
    };
}
#endif
