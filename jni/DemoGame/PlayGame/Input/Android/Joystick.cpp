#ifdef ANDROID_PLATFORM

#include "Joystick.hpp"

using namespace MPACK;

Joystick::Joystick(Vector2f point, Vector2f renderDirection, GLfloat radius)
	: m_pFinger(NULL), m_maxDistance(0.0f)
{
	m_actionCircleCenter=point;
	m_renderDirection=renderDirection;
	m_actionCircleRadius=radius;

	Global::pContext->pInputService->Link_FDOWN(Param2PtrCallbackStruct(DOWN_callback,this));
	Global::pContext->pInputService->Link_FUP(Param2PtrCallbackStruct(UP_callback,this));
}

void Joystick::SetTextures(Texture2D *innerTex, Texture2D *outerTex)
{
	m_outerSprite.SetTexture(outerTex);
	m_innerSprite.SetTexture(innerTex);

	m_outerSprite.SetSize(80.0f,80.0f);
	m_innerSprite.SetSize(60.0f,60.0f);

	m_outerSprite.SetShading(SpriteVertex::ALPHA_BLEND);
	m_innerSprite.SetShading(SpriteVertex::ALPHA_BLEND);

	m_outerSprite.SetLayer(HUD_LAYER);
	m_innerSprite.SetLayer(HUD_LAYER);
}

void Joystick::SetMaxDistance(GLfloat maxDist)
{
	m_maxDistance=maxDist;
}

GLfloat Joystick::GetMaxDistance() const
{
	return m_maxDistance;
}

void Joystick::Update()
{
	if(m_pFinger)
	{
		m_currentPos=m_pFinger->m_pos;
		m_dir=m_currentPos-m_firstPos;
		if(m_dir.Length()>m_maxDistance)
		{
			m_dir.Normalize();
			m_dir*=m_maxDistance;
			m_currentPos=m_firstPos+m_dir;
		}
	}
}

void Joystick::Render()
{
	if(m_pFinger)
	{
		m_outerSprite.m_position=m_firstPos;
		m_innerSprite.m_position=m_currentPos;
	}
	else
	{
		GLfloat dist=m_actionCircleRadius*0.25f;
		m_outerSprite.m_position=m_innerSprite.m_position=m_actionCircleCenter+m_renderDirection*dist;
	}
	m_outerSprite.Render();
	m_innerSprite.Render();
}

void Joystick::Pause()
{
	Global::pContext->pInputService->UnLink_FDOWN(Param2PtrCallbackStruct(DOWN_callback,this));
	Global::pContext->pInputService->UnLink_FUP(Param2PtrCallbackStruct(UP_callback,this));
}

void Joystick::Continue()
{
	Global::pContext->pInputService->Link_FDOWN(Param2PtrCallbackStruct(DOWN_callback,this));
	Global::pContext->pInputService->Link_FUP(Param2PtrCallbackStruct(UP_callback,this));
}

Joystick::~Joystick()
{
}

void Joystick::DOWN_callback(void *param1, void *param2)
{
	Joystick *pJoystick=(Joystick*)(param1);
	if(!pJoystick->m_pFinger)
	{
		Finger *pFinger=(Finger*)(param2);
		if(pFinger->m_flag==Finger::LOCKED)
		{
			return;
		}
		if(pJoystick->m_actionCircleCenter.Distance(pFinger->m_pos)<=pJoystick->m_actionCircleRadius)
		{
			pFinger->m_flag=Finger::LOCKED;
			pJoystick->m_pFinger=pFinger;
			pJoystick->m_firstPos=pFinger->m_pos;
		}
	}
}

void Joystick::UP_callback(void *param1, void *param2)
{
	Joystick *pJoystick=(Joystick*)(param1);
	Finger *pFinger=(Finger*)(param2);
	if(pJoystick->m_pFinger==pFinger)
	{
		pJoystick->m_pFinger->m_flag=Finger::FREE;
		pJoystick->m_pFinger=NULL;
		pJoystick->m_dir=Vector2f();
	}
}

#endif
