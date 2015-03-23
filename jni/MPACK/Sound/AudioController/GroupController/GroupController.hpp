#ifndef MPACK_GROUPCONTROLLER_HPP
#define MPACK_GROUPCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class AudioPlayer;
		class VolumeGroupController;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class GroupController
		{
		public:
			GroupController();
			~GroupController();

			void Add(AudioPlayer *audioPlayer);
			void Clear();

			VolumeGroupController* Volume() const;

		protected:
			std::vector<AudioPlayer*> m_objects;

			VolumeGroupController *m_pVolumeController;

			friend class VolumeGroupController;
		};
	}
}

#endif
