#ifdef ANDROID_PLATFORM

#include "MMAndroidInput.hpp"

#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"

using namespace MPACK;
using namespace MPACK::Core;

MMAndroidInput::MMAndroidInput()
{
	Global::pContext->pInputService->Link_FDOWN(Core::Param2PtrCallbackStruct(MMAndroidInput::DOWNEvent,this));
	Global::pContext->pInputService->Link_FUP(Core::Param2PtrCallbackStruct(MMAndroidInput::UPEvent,this));
}

MMAndroidInput::~MMAndroidInput()
{
}

void MMAndroidInput::Update(GLfloat delta)
{
}

void MMAndroidInput::DOWNEvent(void *pointer1, void *pointer2)
{
	MMAndroidInput *pMMAndroidInput=(MMAndroidInput*)(pointer1);
	for(vector<Param2PtrCallbackStruct>::iterator it=pMMAndroidInput->m_callbackFunc_FDOWN.begin();it!=pMMAndroidInput->m_callbackFunc_FDOWN.end();++it)
	{
		it->function(it->param1,pointer2);
	}
}

void MMAndroidInput::UPEvent(void *pointer1, void *pointer2)
{
	MMAndroidInput *pMMAndroidInput=(MMAndroidInput*)(pointer1);
	for(vector<Param2PtrCallbackStruct>::iterator it=pMMAndroidInput->m_callbackFunc_FUP.begin();it!=pMMAndroidInput->m_callbackFunc_FUP.end();++it)
	{
		it->function(it->param1,pointer2);
	}
}

#endif
