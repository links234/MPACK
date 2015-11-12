#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include "MPACK.hpp"

using namespace MPACK::Math;
using namespace MPACK::Core;
using namespace MPACK::Graphics;
using namespace MPACK::Input;

class Joystick
{
public:
	Joystick(Vector2f point=Vector2f(0.0f,Render::GetScreenHeight()), Vector2f renderDirection=Vector2f(1.0f,-1.0f), GLfloat radius=250.0f);

	void SetTextures(Texture2D *innerTex, Texture2D *outerTex);

	void 	SetMaxDistance(GLfloat maxDist);
	GLfloat GetMaxDistance() const;

	void Update();
	void Render();

	void Pause();
	void Continue();

	~Joystick();

	Vector2f m_dir;

private:
	static void DOWN_callback(void *param1, void *param2);
	static void UP_callback(void *param1, void *param2);

	Finger 		*m_pFinger;
	Vector2f 	m_firstPos,m_currentPos,m_actionCircleCenter,m_renderDirection;
	GLfloat 	m_maxDistance,m_actionCircleRadius;

	Sprite 		m_innerSprite,m_outerSprite;
};

#endif
