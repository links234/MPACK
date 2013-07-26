#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Types.hpp"
#include "Maths.hpp"

#include <vector>

using namespace Math;
using namespace std;

class Object
{
public:
	enum Type
	{
		t_Object,
		t_Enemy,
		t_PhysicalObject,
		t_Player,
		t_Projectile,
		t_SpriteObject
	};

	Object();
	virtual ~Object();

	virtual bool Update(GLfloat delta) = 0;
	virtual void Render() = 0;

	virtual Vector2f GetCameraPosition() const = 0;

	static void UpdateAll(GLfloat delta);
	static void RenderAll();

	bool m_debugInCollision;

	Type m_objectType;

protected:
	static vector<Object*> s_objects;
};

#endif
