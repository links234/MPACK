#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "PGDesktopInput.hpp"

#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"
#include "Camera2D.hpp"
#include "Maths.hpp"

using namespace Core;
using namespace Math;

PGDesktopInput::PGDesktopInput()
{
}

PGDesktopInput::~PGDesktopInput()
{
}

void PGDesktopInput::Update(GLfloat delta)
{
	m_requestExit=false;
	if(Global::pContext->pInputService->GetKeyboard()->KeyPressed(KC_ESCAPE))
	{
		m_requestExit=true;
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

void PGDesktopInput::Render()
{
}

void PGDesktopInput::Pause()
{
}

void PGDesktopInput::Continue()
{
}

Vector2f PGDesktopInput::GetMovementDirection() const
{
	return m_movementDirection;
}

Vector2f PGDesktopInput::GetShootingDirection() const
{
	return Vector2f();
}

bool PGDesktopInput::IsUserRequestingExit()
{
	return m_requestExit;
}

#endif
