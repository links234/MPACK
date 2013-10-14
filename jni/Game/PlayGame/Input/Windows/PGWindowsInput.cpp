#ifdef WINDOWS_PLATFORM

#include "PGWindowsInput.hpp"

#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"
#include "Camera2D.hpp"
#include "Maths.hpp"

using namespace Math;

PGWindowsInput::PGWindowsInput()
{
}

PGWindowsInput::~PGWindowsInput()
{
}

void PGWindowsInput::Update(GLfloat delta)
{
	m_requestExit=false;
	if(Global::pContext->pInputService->KeyPressed(VK_ESCAPE))
	{
		m_requestExit=true;
	}

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

void PGWindowsInput::Render()
{
}

void PGWindowsInput::Pause()
{
}

void PGWindowsInput::Continue()
{
}

Vector2f PGWindowsInput::GetMovementDirection() const
{
	return m_movementDirection;
}

Vector2f PGWindowsInput::GetShootingDirection() const
{
	return Vector2f();
}

bool PGWindowsInput::IsUserRequestingExit()
{
	return m_requestExit;
}

#endif
