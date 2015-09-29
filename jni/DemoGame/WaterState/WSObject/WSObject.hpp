#ifndef WSOBJECT_HPP
#define WSOBJECT_HPP

#include "MPACK.hpp"

#include <vector>

using namespace MPACK;
using namespace MPACK::Math;
using namespace MPACK::Graphics;
using namespace std;

class WSObject : public CameraObject
{
public:
											WSObject();
	virtual									~WSObject();

	virtual bool 							Update(float dtime) = 0;
	virtual void							Render() = 0;

	static bool 							UpdateAll(float dtime);
	static void 							RenderAll();


protected:
	static std::vector <WSObject*>			s_wsObjects;
};

#endif
