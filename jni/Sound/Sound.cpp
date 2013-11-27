#include "Sound.hpp"

#include "Context.hpp"
#include "Resource.hpp"
#include "Log.hpp"

namespace Core
{
    Sound::Sound(const char* pPath)
    	: mBuffer(NULL), mLength(0)
    {
    	mResource = Core::LoadResource(pPath);

		int i;
		for(i = 0; pPath[i] != '\0'; i++)
			;
		i -= 3; //presume 3 char extension

		strcpy(extension, pPath+i);
    }

    Sound::~Sound(){
    	Unload();
    }

    const char* Sound::GetPath()
    {
        return mResource->GetPath();
    }

    ReturnValue Sound::Load()
    {
        //LOGI("Loading sound %s", mResource.GetPath());
        ReturnValue lRes;

        // Opens sound file.
        if (mResource->Open() != RETURN_VALUE_OK)
        {
            return RETURN_VALUE_KO;
        }

        // Reads sound file.
        mLength = mResource->GetLength();

        mBuffer = new uint8_t[mLength];

        lRes = mResource->Read(mBuffer, mLength);
        mResource->Close();

        if (lRes != RETURN_VALUE_OK)
        {
            LOGE("Error while reading PCM sound.");
            return RETURN_VALUE_KO;
        }
        else
        {
            return RETURN_VALUE_OK;
        }
    }

    ReturnValue Sound::Unload()
    {
        delete[] mBuffer;
        mBuffer = NULL; mLength = 0;

        return RETURN_VALUE_OK;
    }


    uint8_t* Sound::GetPCMData()
    {
    	if(!mBuffer)
    	{
    		LOGE("Error: Sound buffer null");
    	}
    	else
    	{
			if(strcmp(extension, "wav") == 0)
			{
				return (mBuffer + 44);
			}
			else
			{
				return mBuffer;
			}
    	}
    	return NULL;
    }


    off_t Sound::GetPCMLength()
    {
    	if(strcmp(extension, "wav") == 0)
    	{
			return (mLength - 44);
    	}
		else
		{
			return mLength;
		}
    }
}
