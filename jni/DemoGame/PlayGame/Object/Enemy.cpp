#include "Enemy.hpp"

#include "MPACK.hpp"

using namespace MPACK::Core;
using namespace MPACK::Physics;

Enemy::Enemy(MPACK::Physics::World *world)
	: PhysicalObject(world), m_angle(0.0f)
{
	m_thisPointer = ToVoidPointer(this);

	vector<Vector2f> vertices;
	vertices.push_back(Vector2f(0.0f,30.0f));
	vertices.push_back(Vector2f(30.0f,30.0f));
	vertices.push_back(Vector2f(40.0f,10.0f));
	vertices.push_back(Vector2f(40.0f,-10.0f));
	vertices.push_back(Vector2f(30.0f,-20.0f));
	vertices.push_back(Vector2f(-10.0f,-20.0f));
	vertices.push_back(Vector2f(-50.0f,-10.0f));
	vertices.push_back(Vector2f(-30.0f,20.0f));


	PolygonShape *poly = new PolygonShape;
	poly->Set(&vertices[0],vertices.size());

	m_shape = poly;
	m_body = m_world->Add(m_shape,0,0);

	Material mat=m_body->GetMaterial();
	mat.density=50.0f;
	m_body->SetMaterial(mat);
	m_body->SetOrientation(0.0f);

	m_body->userData=(void*)&m_thisPointer;
}

Enemy::~Enemy()
{
}

bool Enemy::Update(GLfloat delta)
{
	m_position = m_body->GetPosition();
	m_angle = m_body->GetOrientation();
	return true;
}

void Enemy::Render()
{
	m_sprite->m_position = m_position;
	m_sprite->SetAngle(m_angle);
	SpriteObject::Render();
	PhysicalObject::Render();
}

Vector2f Enemy::GetCameraPosition() const
{
	return m_sprite->m_position;
}
