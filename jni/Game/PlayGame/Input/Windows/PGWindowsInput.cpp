#include "Platform.hpp"

#ifdef WINDOWS_PLATFORM

#include "PGWindowsInput.hpp"

PGWindowsInput::PGWindowsInput()
{
}

PGWindowsInput::~PGWindowsInput()
{
}

void PGWindowsInput::Update(GLfloat delta)
{
}

void PGWindowsInput::Render()
{
}

Vector2f PGWindowsInput::GetMovementDirection() const
{
	return Vector2f();
}

Vector2f PGWindowsInput::GetShootingDirection() const
{
	return Vector2f();
}

bool PGWindowsInput::IsUserRequestingExit() const
{
	return false;
}

#endif
