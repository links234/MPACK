#ifndef MPACK_GROUPCONTROLLER_HPP
#define MPACK_GROUPCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class AudioPlayer;
		class PlayGroupController;
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
			~GroupController();

			void Add(AudioPlayer *audioPlayer);
			void Clear();

			PlayGroupController* Play() const;
			VolumeGroupController* Volume() const;

			static GroupController* Get(std::string name);
			static GroupController* New();

			static void DestroyAll();

		protected:
			GroupController(std::string name=std::string(""));

			std::vector<AudioPlayer*> m_objects;

			PlayGroupController *m_pPlayGroupController;
			VolumeGroupController *m_pVolumeGroupController;

			std::string m_name;

			static std::unordered_map<std::string, GroupController*> s_group;
			static std::unordered_set<GroupController*> s_untrackedGroups;

			friend class PlayGroupController;
			friend class VolumeGroupController;
		};
	}
}

#endif
