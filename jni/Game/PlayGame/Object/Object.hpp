#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Maths.hpp"
#include "Sprite.hpp"

#include <vector>

using namespace std;
using namespace Math;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update(GLfloat delta) = 0;
	virtual void Render() = 0;

	static void UpdateAll(GLfloat delta);
	static void RenderAll();

protected:
	static vector<Object*> s_objects;
};

#endif
