#include "MMInputController.hpp"

#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"

using namespace std;
using namespace MPACK;
using namespace MPACK::Core;

MMInputController::MMInputController()
{
	Global::pContext->pInputService->Link_FDOWN(Core::Param2PtrCallbackStruct(MMInputController::DOWNEvent,this));
	Global::pContext->pInputService->Link_FUP(Core::Param2PtrCallbackStruct(MMInputController::UPEvent,this));
}

MMInputController::~MMInputController()
{
	Global::pContext->pInputService->UnLink_FDOWN(Core::Param2PtrCallbackStruct(MMInputController::DOWNEvent,this));
	Global::pContext->pInputService->UnLink_FUP(Core::Param2PtrCallbackStruct(MMInputController::UPEvent,this));
}

void MMInputController::Update(GLfloat delta)
{
}

void MMInputController::Link_FUP(const Param2PtrCallbackStruct &link)
{
	m_callbackFunc_FUP.push_back(link);
}

void MMInputController::Link_FDOWN(const Param2PtrCallbackStruct &link)
{
	m_callbackFunc_FDOWN.push_back(link);
}

void MMInputController::DOWNEvent(void *pointer1, void *pointer2)
{
	MMInputController *pMMInputController=(MMInputController*)(pointer1);
	for(vector<Param2PtrCallbackStruct>::iterator it=pMMInputController->m_callbackFunc_FDOWN.begin();it!=pMMInputController->m_callbackFunc_FDOWN.end();++it)
	{
		it->function(it->param1,pointer2);
	}
}

void MMInputController::UPEvent(void *pointer1, void *pointer2)
{
	MMInputController *pMMInputController=(MMInputController*)(pointer1);
	for(vector<Param2PtrCallbackStruct>::iterator it=pMMInputController->m_callbackFunc_FUP.begin();it!=pMMInputController->m_callbackFunc_FUP.end();++it)
	{
		it->function(it->param1,pointer2);
	}
}

