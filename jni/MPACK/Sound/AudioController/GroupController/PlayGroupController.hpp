#ifndef MPACK_PLAYGROUPCONTROLLER_HPP
#define MPACK_PLAYGROUPCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class GroupController;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class PlayGroupController
		{
		public:
			~PlayGroupController();

			Core::ReturnValue Start();
			Core::ReturnValue Resume();
			Core::ReturnValue Pause();
			Core::ReturnValue Stop();

		protected:
			PlayGroupController(GroupController *groupController);

			GroupController *m_pGroupController;

			friend class GroupController;
		};
	}
}

#endif
