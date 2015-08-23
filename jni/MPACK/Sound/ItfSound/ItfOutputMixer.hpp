#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFOUTPUTMIXER_HPP
#define MPACK_ITFOUTPUTMIXER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class VolumeController;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class OutputMixer
		{
		public:
			~OutputMixer();

			VolumeController* Volume() const;

			static OutputMixer* GetOutputMixer();
			static void DestroyOutputMixer();

			static void Cleanup();
		private:
			OutputMixer();

			void LoadControllers();

			VolumeController *m_pVolumeController;

			static OutputMixer *s_outputMixer;

			static std::unordered_set<OutputMixer*> s_objects;
		};
	}
}

#endif

#endif
