#ifndef MMINPUTCONTROLLER_HPP
#define MMINPUTCONTROLLER_HPP

#include "MPACK.hpp"

#include <vector>

class MMInputController
{
public:
	MMInputController();
	virtual ~MMInputController();

	virtual void Update(GLfloat delta) = 0;

	void Link_FUP(const MPACK::Core::Param2PtrCallbackStruct &link);
	void Link_FDOWN(const MPACK::Core::Param2PtrCallbackStruct &link);

	static MMInputController* Initialize();

protected:
	std::vector<MPACK::Core::Param2PtrCallbackStruct> m_callbackFunc_FUP;
	std::vector<MPACK::Core::Param2PtrCallbackStruct> m_callbackFunc_FDOWN;
};

#endif
