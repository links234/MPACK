#ifndef MMINPUTCONTROLLER_HPP
#define MMINPUTCONTROLLER_HPP

#include "MPACK.hpp"

#include <vector>

class MMInputController
{
public:
	MMInputController();
	virtual ~MMInputController();

	void Update(GLfloat delta);

	void Link_FUP(const MPACK::Core::Param2PtrCallbackStruct &link);
	void Link_FDOWN(const MPACK::Core::Param2PtrCallbackStruct &link);

protected:
	static void DOWNEvent(void *pointer1, void *pointer2);
	static void UPEvent(void *pointer1, void *pointer2);

	std::vector<MPACK::Core::Param2PtrCallbackStruct> m_callbackFunc_FUP;
	std::vector<MPACK::Core::Param2PtrCallbackStruct> m_callbackFunc_FDOWN;
};

#endif
