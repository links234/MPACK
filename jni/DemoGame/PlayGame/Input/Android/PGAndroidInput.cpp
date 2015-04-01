#ifdef ANDROID_PLATFORM

#include "MPACK.hpp"

#include "PGAndroidInput.hpp"

using namespace MPACK;

PGAndroidInput::PGAndroidInput()
	: m_firstScale(1.0f)
{
	m_requestExit = false;
	Global::pContext->pInputService->Link_KEYBACK(Param1PtrCallbackStruct(onBackKey,this));

	m_joystickInnerTex=new Texture2D;
	m_joystickOuterTex=new Texture2D;

	m_joystickInnerTex->Load("@Sprites/joystick_inner.png");
	m_joystickOuterTex->Load("@Sprites/joystick_outer.png");

	//Joystick setup
	m_movementJoystick=new Joystick;
	m_movementJoystick->SetTextures(m_joystickInnerTex,m_joystickOuterTex);
	m_movementJoystick->SetMaxDistance(100.0f);

	m_aimJoystick=new Joystick(Vector2f(Render::GetScreenWidth(),Render::GetScreenHeight()),Vector2f(-1.0f,-1.0f));
	m_aimJoystick->SetTextures(m_joystickInnerTex,m_joystickOuterTex);
	m_aimJoystick->SetMaxDistance(100.0f);

	//Setup input surface
	m_fingers[0]=m_fingers[1]=NULL;
	Global::pContext->pInputService->Link_FDOWN(Param2PtrCallbackStruct(DOWN_callback,this));
	Global::pContext->pInputService->Link_FUP(Param2PtrCallbackStruct(UP_callback,this));
}

PGAndroidInput::~PGAndroidInput()
{
	delete m_joystickInnerTex;
	delete m_joystickOuterTex;

	delete m_movementJoystick;
	delete m_aimJoystick;
}

void PGAndroidInput::Update(GLfloat delta)
{
	m_movementJoystick->Update();
	m_aimJoystick->Update();

	if(m_fingers[1])
	{
		GLfloat firstDistance=m_firstScalePosition[0].Distance(m_firstScalePosition[1]);
		GLfloat currentDistance=m_fingers[0]->m_pos.Distance(m_fingers[1]->m_pos);
		GLfloat ratio=currentDistance/firstDistance;
		Global::pActiveCamera->SetScale(m_firstScale*ratio);

		GLfloat lastAngle=(m_lastFramePosition[1]-m_lastFramePosition[0]).Angle();
		GLfloat	currentAngle=(m_fingers[1]->m_pos-m_fingers[0]->m_pos).Angle();
		GLfloat angle=currentAngle-lastAngle;
		Global::pActiveCamera->RotateDirection(angle);
	}

	if(m_fingers[0])
	{
		m_lastFramePosition[0]=m_fingers[0]->m_pos;
	}
	if(m_fingers[1])
	{
		m_lastFramePosition[1]=m_fingers[1]->m_pos;
	}
}

void PGAndroidInput::Render()
{
	m_movementJoystick->Render();
	m_aimJoystick->Render();
}

Vector2f PGAndroidInput::GetMovementDirection() const
{
	float acceleration=m_movementJoystick->m_dir.Length()/m_movementJoystick->GetMaxDistance();
	acceleration*=m_maxAcceleration;
	return (m_movementJoystick->m_dir.Normalized()*acceleration).Rotated(Global::pActiveCamera->GetDirection().Angle());
}

Vector2f PGAndroidInput::GetShootingDirection() const
{
	return m_aimJoystick->m_dir.Normalized();
}

bool PGAndroidInput::IsUserRequestingExit()
{
	bool value=m_requestExit;
	m_requestExit=false;
	return value;
}

void PGAndroidInput::Pause()
{
	m_movementJoystick->Pause();
	m_aimJoystick->Pause();
	Global::pContext->pInputService->UnLink_KEYBACK(Param1PtrCallbackStruct(onBackKey,this));
	Global::pContext->pInputService->UnLink_FDOWN(Param2PtrCallbackStruct(DOWN_callback,this));
	Global::pContext->pInputService->UnLink_FUP(Param2PtrCallbackStruct(UP_callback,this));
}

void PGAndroidInput::Continue()
{
	m_movementJoystick->Continue();
	m_aimJoystick->Continue();
	Global::pContext->pInputService->Link_KEYBACK(Param1PtrCallbackStruct(onBackKey,this));
	Global::pContext->pInputService->Link_FDOWN(Param2PtrCallbackStruct(DOWN_callback,this));
	Global::pContext->pInputService->Link_FUP(Param2PtrCallbackStruct(UP_callback,this));
}

void PGAndroidInput::onBackKey(void *pointer)
{
	PGAndroidInput *pPGAndroidInput=(PGAndroidInput*)(pointer);
	pPGAndroidInput->m_requestExit=true;
}

void PGAndroidInput::DOWN_callback(void *param1, void *param2)
{
	PGAndroidInput *pPGAndroidInput=(PGAndroidInput*)(param1);
	Finger *pFinger=(Finger*)(param2);
	if(pFinger->m_flag==Finger::LOCKED)
	{
		return;
	}
	if(pPGAndroidInput->m_fingers[0]==NULL)
	{
		pFinger->m_flag=Finger::LOCKED;
		pPGAndroidInput->m_lastFramePosition[0]=pFinger->m_pos;
		pPGAndroidInput->m_fingers[0]=pFinger;
		return;
	}
	if(pPGAndroidInput->m_fingers[1]==NULL)
	{
		pFinger->m_flag==Finger::LOCKED;
		pPGAndroidInput->m_firstScalePosition[0]=pPGAndroidInput->m_fingers[0]->m_pos;
		pPGAndroidInput->m_firstScalePosition[1]=pFinger->m_pos;
		pPGAndroidInput->m_lastFramePosition[1]=pFinger->m_pos;
		pPGAndroidInput->m_fingers[1]=pFinger;
		pPGAndroidInput->m_firstScale=Global::pActiveCamera->GetScale();
	}
}

void PGAndroidInput::UP_callback(void *param1, void *param2)
{
	PGAndroidInput *pPGAndroidInput=(PGAndroidInput*)(param1);
	Finger *pFinger=(Finger*)(param2);
	if(pPGAndroidInput->m_fingers[1]==pFinger)
	{
		pFinger->m_flag=Finger::FREE;
		pPGAndroidInput->m_fingers[1]=NULL;
		return;
	}
	if(pPGAndroidInput->m_fingers[0]==pFinger)
	{
		pFinger->m_flag==Finger::FREE;
		if(pPGAndroidInput->m_fingers[1]!=NULL)
		{
			pPGAndroidInput->m_fingers[0]=pPGAndroidInput->m_fingers[1];
			pPGAndroidInput->m_lastFramePosition[0]=pPGAndroidInput->m_lastFramePosition[1];
			pPGAndroidInput->m_fingers[1]=NULL;
		}
		else
		{
			pPGAndroidInput->m_fingers[0]=NULL;
		}
	}
}

#endif
