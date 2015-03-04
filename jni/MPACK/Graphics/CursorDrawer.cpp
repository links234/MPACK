#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "CursorDrawer.hpp"
#include "Texture2D.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Graphics
	{
		CursorDrawer CursorDrawer::s_instance;

		#define		CURSOR_LAYER	10000.0f

		CursorDrawer::CursorDrawer()
			: m_hide(false), m_autohide(true), m_autohideTime(5.0f)
		{
			m_pTimer=MPACK::Time::Timer::Create();
			m_pTimer->Start();

			m_pSprite=new Sprite();
			m_pSprite->SetSize(10.0f,10.0f);
			m_pSprite->SetShading(SpriteVertex::ALPHA_TEST);
			m_pSprite->SetLayer(CURSOR_LAYER);
		}

		CursorDrawer::~CursorDrawer()
		{
			delete m_pSprite;
			delete m_pTimer;
		}

		void CursorDrawer::SetIcon(Texture2D *icon)
		{
			m_pSprite->SetTexture(icon);
		}

		void CursorDrawer::SetIconWidth(GLfloat width)
		{
			m_pSprite->SetWidth(width);
		}

		void CursorDrawer::SetIconHeight(GLfloat height)
		{
			m_pSprite->SetHeight(height);
		}

		void CursorDrawer::SetIconSize(GLfloat width, GLfloat height)
		{
			m_pSprite->SetSize(width,height);
		}

		void CursorDrawer::Hide()
		{
			m_hide=true;
		}

		void CursorDrawer::Show()
		{
			m_hide=false;
		}

		void CursorDrawer::EnableAutohide()
		{
			m_autohide=true;
			m_pTimer->Start();
		}

		void CursorDrawer::DisableAutohide()
		{
			m_autohide=false;
		}

		void CursorDrawer::Update()
		{
			if(m_autohide)
			{
				if(Global::pContext->pInputService->GetMouse()->Moved())
				{
					m_pTimer->Start();
				}
			}
		}

		void CursorDrawer::Render()
		{
			if(m_hide)
			{
				return;
			}

			if(m_pTimer->Time()>m_autohideTime && m_autohide)
			{
				return;
			}

			m_pSprite->m_position=Global::pContext->pInputService->GetMouse()->GetPosition();
			m_pSprite->m_position.x+=m_pSprite->GetWidth()*0.5;
			m_pSprite->m_position.y+=m_pSprite->GetHeight()*0.5;

			m_pSprite->Render();
		}

		CursorDrawer* CursorDrawer::GetInstance()
		{
			return &s_instance;
		}
	}
}

#endif
