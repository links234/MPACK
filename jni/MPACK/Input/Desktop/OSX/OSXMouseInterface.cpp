#ifdef OSX_PLATFORM

#include "OSXMouseInterface.hpp"

#include "OSXEventLoop.hpp"

#include "Global.hpp"

namespace MPACK
{
	namespace Input
	{
		OSXMouseInterface::OSXMouseInterface()
		{
		}

		OSXMouseInterface::~OSXMouseInterface()
		{
		}

		void OSXMouseInterface::Update()
		{
			memcpy(m_pLastState,m_pCurrState,sizeof(m_stateBuffer1));
		}
	}
}

#endif
