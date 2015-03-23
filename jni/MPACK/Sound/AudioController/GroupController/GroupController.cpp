#include "GroupController.hpp"

#include "AudioPlayer.hpp"
#include "VolumeGroupController.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		GroupController::GroupController()
		{
			m_pVolumeController = new VolumeGroupController(this);
		}

		GroupController::~GroupController()
		{
			delete m_pVolumeController;
		}

		void GroupController::Add(AudioPlayer *audioPlayer)
		{
			m_objects.push_back(audioPlayer);
		}

		void GroupController::Clear()
		{
			m_objects.clear();
		}

		VolumeGroupController* GroupController::Volume() const
		{
			return m_pVolumeController;
		}
	}
}
