#ifndef MMINPUTCONTROLLER_HPP
#define MMINPUTCONTROLLER_HPP

#include "Types.hpp"

#include <vector>

using namespace Core;
using namespace std;

class MMInputController
{
public:
	MMInputController();
	virtual ~MMInputController();

	virtual void Update(GLfloat delta) = 0;

	void Link_FUP(const Param2PtrCallbackStruct &link);
	void Link_FDOWN(const Param2PtrCallbackStruct &link);

	static MMInputController* Initialize();

protected:
	vector<Param2PtrCallbackStruct> m_callbackFunc_FUP;
	vector<Param2PtrCallbackStruct> m_callbackFunc_FDOWN;
};

#endif
