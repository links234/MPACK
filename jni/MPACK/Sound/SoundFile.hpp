#ifndef MPACK_SOUNDFILE_HPP
#define MPACK_SOUNDFILE_HPP

class SoundService;

#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class Resource;
	}

	namespace Sound
	{
		class Sound
		{
		public:
			Sound(const char* pPath);
			~Sound();

			const char* GetPath();

			Core::ReturnValue Load();
			Core::ReturnValue Unload();

			uint8_t* GetPCMData();
			off_t GetPCMLength();

		private:
			friend class SoundService;

		private:
			Core::Resource* mResource;
			uint8_t* mBuffer; off_t mLength;
			char extension[4];
		};
	}
}

#endif
