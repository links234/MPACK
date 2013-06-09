#include "Log.hpp"
#include "Global.hpp"
#include "Asset.hpp"

#include <cstring>

namespace Core
{
	Asset::Asset(const char* pPath):
        Resource(pPath),
        mAsset(NULL),
        mBuffer(NULL)
	{
    }

    Status Asset::Open()
    {
        mAsset = AAssetManager_open(Global::pAAssetManager, mPath, AASSET_MODE_UNKNOWN);
        if(mAsset == NULL)
        {
        	LOGE("Failed to open asset: %s",mPath);
        }
        return (mAsset != NULL) ? STATUS_OK : STATUS_KO;
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

    Status Asset::Read(void* pBuffer, size_t pCount)
    {
        int32_t lReadCount = AAsset_read(mAsset, pBuffer, pCount);
        return (lReadCount == pCount) ? STATUS_OK : STATUS_KO;
    }

    off_t Asset::GetLength()
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
