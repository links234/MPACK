#ifndef TILEDBACKGROUND_HPP
#define TILEDBACKGROUND_HPP

#include "Sprite.hpp"

class TiledBackground: public Sprite
{
public:
	TiledBackground();
	virtual ~TiledBackground();

	virtual void Render();

	void EnableCamera();
	void DisableCamera();

	bool IsCameraEnabled() const;

	void SetDepth(const GLfloat depth);
	GLfloat GetDepth() const;

protected:
	GLfloat m_depth;

	bool m_isCameraEnabled;
};

#endif
