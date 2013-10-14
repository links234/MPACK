#ifdef WINDOWS_PLATFORM

#ifndef CURSOR_HPP
#define CURSOR_HPP

#include "Types.hpp"

class Sprite;
namespace Core
{
	class Texture2D;
	class Timer;
}

class Cursor
{
public:
	void Update();
	void Render();
	void SetIcon(Core::Texture2D *icon);
	void SetIconWidth(GLfloat width);
	void SetIconHeight(GLfloat height);
	void SetIconSize(GLfloat width, GLfloat height);
	void Hide();
	void Show();
	void EnableAutohide();
	void DisableAutohide();

	static Cursor* GetInstance();

private:
	Cursor();
	~Cursor();

	void InitBuffers();

	Sprite				*m_pSprite;
	GLfloat				m_autohideTime;
	bool				m_hide;
	bool				m_autohide;
	Core::Timer			*m_pTimer;

	static Cursor s_instance;
	
};

#endif

#endif
