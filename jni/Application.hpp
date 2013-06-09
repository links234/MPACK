#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "ActivityHandler.hpp"
#include "GameState.hpp"
#include "Context.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>

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
        GameState *m_pGameState;
    };
}
#endif
