#include "Sound.hpp"
#include "Log.hpp"

namespace Core
{
    Sound::Sound(const char* pPath) :
        mResource(pPath),
        mBuffer(NULL), mLength(0)
    {
    }

    const char* Sound::GetPath()
    {
        return mResource.GetPath();
    }

    Status Sound::Load()
    {
        LOGI("Loading sound %s", mResource.GetPath());
        Status lRes;

        // Opens sound file.
        if (mResource.Open() != STATUS_OK)
        {
            return STATUS_KO;
        }

        // Reads sound file.
        mLength = mResource.GetLength();
        mBuffer = new uint8_t[mLength];
        lRes = mResource.Read(mBuffer, mLength);
        mResource.Close();

        if (lRes != STATUS_OK)
        {
            LOGE("Error while reading PCM sound.");
            return STATUS_KO;
        }
        else
        {
            return STATUS_OK;
        }
    }

    Status Sound::Unload()
    {
        delete[] mBuffer;
        mBuffer = NULL; mLength = 0;

        return STATUS_OK;
    }
}
