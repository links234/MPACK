#include "Enemy.hpp"

Enemy::Enemy()
{

	vector<Vector2f> vertices;
	vertices.push_back(Vector2f(0.0f,30.0f));
	vertices.push_back(Vector2f(30.0f,30.0f));
	vertices.push_back(Vector2f(40.0f,10.0f));
	vertices.push_back(Vector2f(40.0f,-10.0f));
	vertices.push_back(Vector2f(30.0f,-20.0f));
	vertices.push_back(Vector2f(-10.0f,-20.0f));
	vertices.push_back(Vector2f(-50.0f,-10.0f));
	vertices.push_back(Vector2f(-30.0f,20.0f));


	PPoly *poly=(PPoly*)m_shape;
	poly->Set(&vertices[0],vertices.size());
}

Enemy::~Enemy()
{
}

bool Enemy::Update(GLfloat delta)
{
	m_angle=m_linearVelocity.Angle();
	m_sprite->m_position=m_position;
	m_sprite->SetAngle(m_angle);
	return true;
}

void Enemy::Render()
{
	SpriteObject::Render();
	PhysicalObject::Render();
}

Vector2f Enemy::GetCameraPosition() const
{
	return m_sprite->m_position;
}
