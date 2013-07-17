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

	void SetUVScale(const GLfloat uScale, const GLfloat vScale);

	void SetUScale(const GLfloat uScale);
	GLfloat GetUScale() const;

	void SetVScale(const GLfloat vScale);
	GLfloat GetVScale() const;

protected:
	GLfloat m_depth;
	GLfloat	m_uScale;
	GLfloat m_vScale;

	bool m_isCameraEnabled;
};

#endif
