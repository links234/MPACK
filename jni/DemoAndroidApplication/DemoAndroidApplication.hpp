#ifndef DEMOAPPLICATION_HPP
#define DEMOAPPLICATION_HPP

#include "MPACK.hpp"

namespace Demo
{
	class GameState;
}

namespace Demo
{
	enum
	{
		EVENT_NOTHING,
		EVENT_MAINMENU_CONTINUE,
		EVENT_MAINMENU_NEWGAME,
		EVENT_MAINMENU_WATER,
		EVENT_MAINMENU_HIGHSCORE,
		EVENT_MAINMENU_CREDITS,
		EVENT_MAINMENU_EXIT,
		EVENT_PLAYGAME_PAUSE,
		EVENT_PLAYGAME_EXIT,
		EVENT_WATER_PAUSE,
		EVENT_WATER_EXIT
	};

    class AndroidApplication : public MPACK::Core::AndroidApplication
    {
    public:
    	AndroidApplication();
    	~AndroidApplication();

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
