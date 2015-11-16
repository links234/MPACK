#ifdef ANDROID_PLATFORM

#include "Asset.hpp"

#include "Log.hpp"
#include "Global.hpp"

#include <cstring>

namespace MPACK
{
	namespace Core
	{
		Asset::Asset(const char* pPath):
			InputResource(pPath),
			mAsset(NULL),
			mBuffer(NULL)
		{
		}

		ReturnValue Asset::Open()
		{
			mAsset = AAssetManager_open(Global::pAAssetManager, mPath, AASSET_MODE_UNKNOWN);
			if(mAsset == NULL)
			{
				LOGE("Asset::Open() error: failed to open asset: %s",mPath);
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

		ReturnValue Asset::Read(void* pBuffer, size_t count)
		{
			int32_t lReadCount = AAsset_read(mAsset, pBuffer, count);
			return (lReadCount == count) ? RETURN_VALUE_OK : RETURN_VALUE_KO;
		}

		ReturnValue Asset::ReadFrom(int offset, void* pBuffer, size_t count)
		{
			int oldOffset=GetOffset();
			SetOffset(offset);
			Read(pBuffer,count);
			SetOffset(oldOffset);
		}

		const void* Asset::Bufferize()
		{
			if(!mAsset)
			{
				LOGE("Asset::Bufferize() error: asset is not opened");
				return NULL;
			}
			int length=AAsset_getLength(mAsset);
			mBuffer=new char[length+1];
			memcpy(mBuffer,AAsset_getBuffer(mAsset),length);
			mBuffer[length]=0;
			return mBuffer;
		}

		int Asset::GetOffset()
		{
			if(!mAsset)
			{
				return 0;
			}
			else
			{
				return AAsset_getLength(mAsset)-AAsset_getRemainingLength(mAsset);
			}
		}

		void Asset::SetOffset(int offset)
		{
			if(mAsset)
			{
				AAsset_seek(mAsset,offset,SEEK_SET);
			}
		}

		void Asset::Skip(int bytes)
		{
			if(mAsset)
			{
				int offset=GetOffset();
				SetOffset(offset+bytes);
			}
		}

		int Asset::GetLength()
		{
			if(!mAsset)
			{
				LOGE("Asset::GetLength() error: asset is not opened");
				return 0;
			}
			return AAsset_getLength(mAsset);
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
}

#endif
