#ifdef ANDROID_PLATFORM

#ifndef PGANDROIDINPUT_HPP
#define PGANDROIDINPUT_HPP

#include "PGInputController.hpp"

#include "Joystick.hpp"

class PGAndroidInput : public PGInputController
{
public:
	PGAndroidInput();
	virtual ~PGAndroidInput();

	virtual void Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f 	GetMovementDirection() const;
	virtual Vector2f 	GetShootingDirection() const;
	virtual bool 		IsUserRequestingExit();

	virtual void Pause();
	virtual void Continue();

private:
	static void onBackKey(void *pointer);

	static void DOWN_callback(void *param1, void *param2);
	static void UP_callback(void *param1, void *param2);

	bool 		m_requestExit;

	Texture2D	*m_joystickInnerTex;
	Texture2D	*m_joystickOuterTex;
	Joystick 	*m_movementJoystick;
	Joystick	*m_aimJoystick;

	Finger		*m_fingers[2];
	Vector2f	m_firstScalePosition[2];
	Vector2f	m_lastFramePosition[2];
	GLfloat		m_firstScale;
};

#endif

#endif
