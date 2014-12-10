#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Types.hpp"
#include "Math.hpp"

#include <vector>

using namespace Math;
using namespace std;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual bool Update(GLfloat delta) = 0;
	virtual void Render() = 0;

	virtual Vector2f GetCameraPosition() const = 0;

	static void UpdateAll(GLfloat delta);
	static void RenderAll();

	bool m_debugInCollision;

protected:
	static vector<Object*> s_objects;
};

#endif
