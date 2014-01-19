#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "PGDesktopInput.hpp"

#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"
#include "Camera2D.hpp"
#include "Maths.hpp"

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
#ifdef WINDOWS_PLATFORM
	if(Global::pContext->pInputService->KeyPressed(VK_ESCAPE))
	{
		m_requestExit=true;
	}
#endif

	m_movementDirection=Vector2f();
	if(Global::pContext->pInputService->KeyPressed('A'))
	{
		m_movementDirection+=Vector2f(-1.0f,0.0f);
	}
	if(Global::pContext->pInputService->KeyPressed('D'))
	{
		m_movementDirection+=Vector2f(1.0f,0.0f);
	}
	if(Global::pContext->pInputService->KeyPressed('W'))
	{
		m_movementDirection+=Vector2f(0.0f,-1.0f);
	}
	if(Global::pContext->pInputService->KeyPressed('S'))
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
