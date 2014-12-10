#ifndef MPACK_SOUNDFILE_HPP
#define MPACK_SOUNDFILE_HPP

class SoundService;

#include "Types.hpp"

namespace Core
{
	class Resource;
}

namespace Core
{
    class Sound
    {
    public:
        Sound(const char* pPath);
        ~Sound();

        const char* GetPath();

        ReturnValue Load();
        ReturnValue Unload();

        uint8_t* GetPCMData();
        off_t GetPCMLength();

    private:
        friend class SoundService;

    private:
        Resource* mResource;
        uint8_t* mBuffer; off_t mLength;
        char extension[4];
    };
}
#endif
