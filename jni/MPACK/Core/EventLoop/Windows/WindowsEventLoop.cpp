#ifdef WINDOWS_PLATFORM

#include "WindowsEventLoop.hpp"

#include "Application.hpp"
#include "Context.hpp"
#include "TimeService.hpp"
#include "InputService.hpp"
#include "Global.hpp"
#include "Render.hpp"
#include "Log.hpp"

using namespace MPACK::Graphics;

namespace MPACK
{
	namespace Core
	{
		typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );

		WindowsEventLoop::WindowsEventLoop(void *data)
			: m_isFullscreen(false), m_isRunning(false), m_pHInstance((HINSTANCE*)data), m_width(0), m_height(0), m_enabled(false)
		{
		}

		ReturnValue WindowsEventLoop::Run(Application* pApplication)
		{
			m_pApplication = pApplication;
			m_isRunning=true;

			InitializeDisplay();
			m_pApplication->onActivate();

			// Global step loop.
			while(m_isRunning)
			{
				ProcessEvents();
				if(m_pApplication->onStep() != RETURN_VALUE_OK)
				{
					m_isRunning=false;
				}
				SwapBuffers();
			}

			m_pApplication->onDeactivate();
			DestroyDisplay();
			return RETURN_VALUE_OK;
		}

		void WindowsEventLoop::ShowCursor()
		{
			::ShowCursor(true);
		}

		void WindowsEventLoop::HideCursor()
		{
			::ShowCursor(false);
		}

		void* WindowsEventLoop::GetWindowHandle() const
		{
			return (void*)(&m_hwnd);
		}

		ReturnValue WindowsEventLoop::InitializeDisplay()
		{
			int width=800;
			int height=600;
			int bpp=32;
			bool fullscreen=false;

			m_width=width;
			m_height=height;

			DWORD      dwExStyle;
			DWORD      dwStyle;

			m_isFullscreen = fullscreen;

			m_windowRect.left = (long)0;
			m_windowRect.right = (long)width;
			m_windowRect.top = (long)0;
			m_windowRect.bottom = (long)height;

			m_windowClass.cbSize          = sizeof(WNDCLASSEX);
			m_windowClass.style           = CS_HREDRAW | CS_VREDRAW;
			m_windowClass.lpfnWndProc     = WindowsEventLoop::StaticWndProc;
			m_windowClass.cbClsExtra      = 0;
			m_windowClass.cbWndExtra      = 0;
			m_windowClass.hInstance       = *m_pHInstance;
			m_windowClass.hIcon           = LoadIcon(NULL, IDI_APPLICATION);
			m_windowClass.hCursor         = NULL;
			m_windowClass.hbrBackground   = NULL;
			m_windowClass.lpszMenuName    = NULL;
			m_windowClass.lpszClassName   = "FrameworkClass";
			m_windowClass.hIconSm         = LoadIcon(NULL, IDI_WINLOGO);

			if (!RegisterClassEx(&m_windowClass))
			{
				return RETURN_VALUE_KO;
			}

			if (m_isFullscreen)
			{
				DEVMODE dmScreenSettings;

				memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
				dmScreenSettings.dmSize = sizeof(dmScreenSettings);

				dmScreenSettings.dmPelsWidth = width;
				dmScreenSettings.dmPelsHeight = height;
				dmScreenSettings.dmBitsPerPel = bpp;
				dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				{
					LOGE("Display mode failed");
					MessageBox(NULL, "Display mode failed", NULL, MB_OK);
					m_isFullscreen = false;
				}
			}

			if (m_isFullscreen)
			{
				dwExStyle = WS_EX_APPWINDOW;
				dwStyle = WS_POPUP;
			}
			else
			{
				dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
				dwStyle = WS_OVERLAPPEDWINDOW;
			}

			AdjustWindowRectEx(&m_windowRect, dwStyle, false, dwExStyle);

			LOGI("Creating window");
			m_hwnd = CreateWindowEx(NULL,
				"FrameworkClass",
				"Framework",
				dwStyle | WS_CLIPCHILDREN |
				WS_CLIPSIBLINGS,
				0, 0,
				m_windowRect.right - m_windowRect.left,
				m_windowRect.bottom - m_windowRect.top,
				NULL,
				NULL,
				*m_pHInstance,
				this);

			if (!m_hwnd)
			{
				LOGE("WINDOW NOT CREATED!");
				LOGE("Code %d",  GetLastError());
				return RETURN_VALUE_KO;
			}
			LOGI("Window created");
			m_hdc = GetDC(m_hwnd);

			ShowWindow(m_hwnd, SW_SHOW);
			UpdateWindow(m_hwnd);
			return RETURN_VALUE_OK;
		}

		void WindowsEventLoop::DestroyDisplay()
		{
			if (m_isFullscreen)
			{
				ChangeDisplaySettings(NULL, 0);
			}
		}

		void WindowsEventLoop::SetupPixelFormat(void)
		{
			int pixelFormat;

			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),  // size
					1,                          // version
					PFD_SUPPORT_OPENGL |        // OpenGL window
					PFD_DRAW_TO_WINDOW |        // render to window
					PFD_DOUBLEBUFFER,           // support double-buffering
					PFD_TYPE_RGBA,              // color type
					32,                         // prefered color depth
					0, 0, 0, 0, 0, 0,           // color bits (ignored)
					0,                          // no alpha buffer
					0,                          // alpha bits (ignored)
					0,                          // no accumulation buffer
					0, 0, 0, 0,                 // accum bits (ignored)
					16,                         // depth buffer
					0,                          // no stencil buffer
					0,                          // no auxiliary buffers
					PFD_MAIN_PLANE,             // main layer
					0,                          // reserved
					0, 0, 0,                    // no layer, visible, damage masks
			};

			pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
			SetPixelFormat(m_hdc, pixelFormat, &pfd);
		}

		void WindowsEventLoop::ProcessEvents()
		{
			Global::pContext->pTimeService->Update();
			Global::pContext->pInputService->Update();
			MSG msg;
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		void WindowsEventLoop::SwapBuffers()
		{
			::SwapBuffers(m_hdc);
		}

		LRESULT WindowsEventLoop::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			int zDelta=0;

			switch(uMsg)
			{
				case WM_CREATE:
				{
					m_hdc = GetDC(hWnd);
					SetupPixelFormat();

					int attribs[] = {
						WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
						WGL_CONTEXT_MINOR_VERSION_ARB, 0,
					0};

					HGLRC tmpContext = wglCreateContext(m_hdc);
					wglMakeCurrent(m_hdc, tmpContext);

					wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");

					if (!wglCreateContextAttribsARB)
					{
						//m_logger->Print(CLogger::Failure,"OpenGL 3.0 is not supported, falling back to GL 2.1");
						m_hglrc = tmpContext;
					}
					else
					{
						m_hglrc = wglCreateContextAttribsARB(m_hdc, 0, attribs);
						wglDeleteContext(tmpContext);
					}

					wglMakeCurrent(m_hdc, m_hglrc);

					m_isRunning = true;
				}
				break;
				case WM_DESTROY:
				case WM_CLOSE:
					wglMakeCurrent(m_hdc, NULL);
					wglDeleteContext(m_hglrc);
					m_isRunning = false;
					PostQuitMessage(0);
					return 0;
				break;
				case WM_SIZE:
				{
					m_height = HIWORD(lParam);
					m_width = LOWORD(lParam);
					m_pApplication->onDeactivate();
					Render::SetScreenSize(m_width,m_height);
					m_pApplication->onActivate();
				}
				break;
				case WM_KEYDOWN:
					Global::pContext->pInputService->GetKeyboard()->HandleKeyDown(Global::pContext->pInputService->GetKeyboard()->TranslateCode(wParam));
				break;
				case WM_KEYUP:
					Global::pContext->pInputService->GetKeyboard()->HandleKeyUp(Global::pContext->pInputService->GetKeyboard()->TranslateCode(wParam));
				break;
				case WM_MOUSEWHEEL:
					zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
					//m_input->m_currMouse->Wheel+=zDelta;
				break;
				case WM_KILLFOCUS:
					m_enabled=true;
				break;
				case WM_SETFOCUS:
					m_enabled=false;
				break;
				default:
				break;
			}

			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		LRESULT CALLBACK WindowsEventLoop::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			WindowsEventLoop* pWindowsEventLoop = NULL;

			if(uMsg == WM_CREATE)
			{
				pWindowsEventLoop = (WindowsEventLoop*)((LPCREATESTRUCT)lParam)->lpCreateParams;
				SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)pWindowsEventLoop);
			}
			else
			{
				pWindowsEventLoop = (WindowsEventLoop*)GetWindowLongPtr(hWnd, GWL_USERDATA);

				if(!pWindowsEventLoop)
				{
					return DefWindowProc(hWnd, uMsg, wParam, lParam);
				}
			}

			return pWindowsEventLoop->WndProc(hWnd, uMsg, wParam, lParam);
		}
	}
}

#endif
