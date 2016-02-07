#ifdef OSX_PLATFORM

#ifndef MPACK_OSXMOUSEINTERFACE_HPP
#define MPACK_OSXMOUSEINTERFACE_HPP

#include "MouseInterface.hpp"

namespace MPACK
{
	namespace Input
	{
		class OSXMouseInterface : public MouseInterface
		{
		public:
			OSXMouseInterface();
			~OSXMouseInterface();

			void Update();
		};
	}
}

#endif

#endif
