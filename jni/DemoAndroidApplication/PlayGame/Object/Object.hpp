#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "MPACK.hpp"

#include <vector>

using namespace MPACK::Math;
using namespace MPACK::Graphics;
using namespace std;

class Object : public CameraObject
{
public:
	Object();
	virtual ~Object();

	virtual bool Update(GLfloat delta) = 0;
	virtual void Render() = 0;

	static void UpdateAll(GLfloat delta);
	static void RenderAll();
	static void ClearAll();

	bool m_debugInCollision;

protected:
	static vector<Object*> s_objects;
};

#endif
