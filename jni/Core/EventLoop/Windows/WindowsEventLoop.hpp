#include "Platform.hpp"

#ifdef WINDOWS_PLATFORM

#ifndef WINDOWSEVENTLOOP_HPP
#define WINDOWSEVENTLOOP_HPP

#include "Types.hpp"
#include "EventLoop.hpp"

namespace Core
{
	class ActivityHandler;
}

namespace Core
{
    class WindowsEventLoop : public EventLoop
    {
    public:
    	WindowsEventLoop(void *data);
        Status Run(ActivityHandler* pActivityHandler);

    protected:
        static LRESULT CALLBACK StaticWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

        Status InitializeDisplay();
        void DestroyDisplay();

        void SetupPixelFormat();

        void ProcessEvents();
        void SwapBuffers();

        bool	m_isRunning;
		bool	m_isFullscreen;
		bool	m_enabled;

		HWND		m_hwnd;
		HGLRC		m_hglrc;
		HDC			m_hdc;
		RECT		m_windowRect;
		HINSTANCE	*m_pHInstance;
		WNDCLASSEX	m_windowClass;
		GLuint		m_width;
		GLuint		m_height;
    };
}
#endif

#endif

