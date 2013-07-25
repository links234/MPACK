#include "Platform.hpp"

#ifdef WINDOWS_PLATFORM

#include "Cursor.hpp"
#include "Texture2D.hpp"
#include "Sprite.hpp"
#include "WindowsTimer.hpp"
#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"

using namespace Core;

Cursor Cursor::s_instance;

#define		CURSOR_LAYER	10000.0f

Cursor::Cursor()
	: m_hide(false), m_autohide(true), m_autohideTime(5.0f)
{
	m_pTimer=Timer::Create();
	m_pTimer->Start();

	m_pSprite=new Sprite();
	m_pSprite->SetSize(10.0f,10.0f);
	m_pSprite->SetShading(SpriteVertex::ALPHA_TEST);
	m_pSprite->SetLayer(CURSOR_LAYER);
}

Cursor::~Cursor()
{
	delete m_pSprite;
	delete m_pTimer;
}

void Cursor::SetIcon(Texture2D *icon)
{
	m_pSprite->SetTexture(icon);
}

void Cursor::SetIconWidth(GLfloat width)
{
	m_pSprite->SetWidth(width);
}

void Cursor::SetIconHeight(GLfloat height)
{
	m_pSprite->SetHeight(height);
}

void Cursor::SetIconSize(GLfloat width, GLfloat height)
{
	m_pSprite->SetSize(width,height);
}

void Cursor::Hide()
{
	m_hide=true;
}

void Cursor::Show()
{
	m_hide=false;
}

void Cursor::EnableAutohide()
{
	m_autohide=true;
	m_pTimer->Start();
}

void Cursor::DisableAutohide()
{
	m_autohide=false;
}

void Cursor::Update()
{
	if(m_autohide)
	{
		if(m_pTimer->Time()>m_autohideTime)
		{
			if((*Global::pContext->pInputService->m_currMouse)!=(*Global::pContext->pInputService->m_lastMouse))
			{
				m_pTimer->Start();
			}
		}
	}
}

void Cursor::Render()
{
	if(m_pTimer->Time()<=m_autohideTime)
	{
		if(!m_hide)
		{
			m_pSprite->m_position=Global::pContext->pInputService->m_currMouse->Pos;
			m_pSprite->m_position.x+=m_pSprite->GetWidth()*0.5;
			m_pSprite->m_position.y+=m_pSprite->GetHeight()*0.5;
			m_pSprite->Render();
		}
	}
}

Cursor* Cursor::GetInstance()
{
	return &s_instance;
}

#endif
