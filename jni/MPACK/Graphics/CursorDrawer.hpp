#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_CURSORDRAWER_HPP
#define MPACK_CURSORDRAWER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Sprite;
		class Texture2D;
	}
	namespace Time
	{
		class Timer;
	}

	namespace Graphics
	{
		class CursorDrawer
		{
		public:
			void Update();
			void Render();
			void SetIcon(Graphics::Texture2D *icon);
			void SetIconWidth(GLfloat width);
			void SetIconHeight(GLfloat height);
			void SetIconSize(GLfloat width, GLfloat height);
			void Hide();
			void Show();
			void EnableAutohide();
			void DisableAutohide();

			static CursorDrawer* GetInstance();

		private:
			CursorDrawer();
			~CursorDrawer();

			void InitBuffers();

			Sprite				*m_pSprite;
			GLfloat				m_autohideTime;
			bool				m_hide;
			bool				m_autohide;
			MPACK::Time::Timer	*m_pTimer;

			static CursorDrawer s_instance;
		};
	}
}

#endif

#endif
