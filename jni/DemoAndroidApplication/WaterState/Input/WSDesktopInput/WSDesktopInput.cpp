#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "WSDesktopInput.hpp"

#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"
#include "Camera2D.hpp"
#include "Math.hpp"

using namespace MPACK;
using namespace MPACK::Input;
using namespace MPACK::Math;

WSDesktopInput::WSDesktopInput()
{
}

WSDesktopInput::~WSDesktopInput()
{
}

void WSDesktopInput::Update(GLfloat delta)
{
	m_requestExit=false;
	m_userPressedLeftClick = false;
	m_userIsPressingLeftClick = false;
	if(Global::pContext->pInputService->GetKeyboard()->KeyPressed(KC_ESCAPE))
	{
		m_requestExit=true;
	}

	if (Global::pContext->pInputService->GetMouse()->ButtonUp(MBC_LEFT))
	{
		m_userPressedLeftClick = true;
	}

	if (Global::pContext->pInputService->GetMouse()->ButtonPressed(MBC_LEFT))
	{
		m_userIsPressingLeftClick = true;
	}

	m_movementDirection=Vector2f();
	if(Global::pContext->pInputService->GetKeyboard()->KeyPressed(KC_A))
	{
		m_movementDirection+=Vector2f(-1.0f,0.0f);
	}
	if(Global::pContext->pInputService->GetKeyboard()->KeyPressed(KC_D))
	{
		m_movementDirection+=Vector2f(1.0f,0.0f);
	}
	if(Global::pContext->pInputService->GetKeyboard()->KeyPressed(KC_W))
	{
		m_movementDirection+=Vector2f(0.0f,-1.0f);
	}
	if(Global::pContext->pInputService->GetKeyboard()->KeyPressed(KC_S))
	{
		m_movementDirection+=Vector2f(0.0f,1.0f);
	}
	m_movementDirection.Normalize();
	m_movementDirection*=m_maxAcceleration;
	m_movementDirection.Rotate(Global::pActiveCamera->GetDirection().Angle());
}

void WSDesktopInput::Render()
{
}

void WSDesktopInput::Pause()
{
}

void WSDesktopInput::Continue()
{
}

Vector2f WSDesktopInput::GetMovementDirection() const
{
	return m_movementDirection;
}

Vector2f WSDesktopInput::GetShootingDirection() const
{
	return Vector2f();
}

bool WSDesktopInput::IsUserRequestingExit()
{
	return m_requestExit;
}

bool WSDesktopInput::GetLeftMouseButtonUp()
{
	return m_userPressedLeftClick;
}

bool WSDesktopInput::GetLeftMouseButtonPressed()
{
	return m_userIsPressingLeftClick;
}

Vector2f WSDesktopInput::GetMousePosition()
{
	return Global::pContext->pInputService->GetMouse()->GetPosition();
}

#endif
