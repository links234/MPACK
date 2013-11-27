#ifdef ANDROID_PLATFORM

#include "Asset.hpp"

#include "Log.hpp"
#include "Global.hpp"

#include <cstring>

namespace Core
{
	Asset::Asset(const char* pPath):
        Resource(pPath),
        mAsset(NULL),
        mBuffer(NULL)
	{
    }

	ReturnValue Asset::Open()
    {
        mAsset = AAssetManager_open(Global::pAAssetManager, mPath, AASSET_MODE_UNKNOWN);
        if(mAsset == NULL)
        {
        	LOGE("Failed to open asset: %s",mPath);
        }
        return (mAsset != NULL) ? RETURN_VALUE_OK : RETURN_VALUE_KO;
    }

    void Asset::Close()
    {
        if (mAsset != NULL)
        {
            AAsset_close(mAsset);
            mAsset = NULL;
        }

        if (mBuffer != NULL)
        {
        	delete[] mBuffer;
        	mBuffer = NULL;
        }
    }

    ReturnValue Asset::Read(void* pBuffer, size_t pCount)
    {
        int32_t lReadCount = AAsset_read(mAsset, pBuffer, pCount);
        return (lReadCount == pCount) ? RETURN_VALUE_OK : RETURN_VALUE_KO;
    }

    int Asset::GetLength()
    {
        return AAsset_getLength(mAsset);
    }

    const void* Asset::Bufferize()
    {
    	int length=AAsset_getLength(mAsset);
    	mBuffer=new char[length+1];
    	memcpy(mBuffer,AAsset_getBuffer(mAsset),length);
    	mBuffer[length]=0;
        return mBuffer;
    }

    Asset::~Asset()
    {
    	Close();
    }

    AssetDescriptor Asset::Descript()
    {
    	AssetDescriptor lDescriptor = { -1, 0, 0 };
        AAsset* lAsset = AAssetManager_open(Global::pAAssetManager, mPath, AASSET_MODE_UNKNOWN);
        if (lAsset != NULL)
        {
            lDescriptor.mDescriptor = AAsset_openFileDescriptor(lAsset, &lDescriptor.mStart, &lDescriptor.mLength);
            AAsset_close(lAsset);
        }
        return lDescriptor;
    }
}

#endif
