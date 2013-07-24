#include "Platform.hpp"

#ifdef ANDROID_PLATFORM

#ifndef ASSET_HPP
#define ASSET_HPP

#include "Resource.hpp"
#include "Types.hpp"

namespace Core
{
    struct AssetDescriptor
    {
        int32_t mDescriptor;
        off_t mStart;
        off_t mLength;
    };

    class Asset : public Resource
    {
    public:
        Asset(const char* pPath);

        virtual Status Open();
        virtual void Close();
        virtual Status Read(void* pBuffer, size_t pCount);

        virtual off_t GetLength();
        virtual const void* Bufferize();

        virtual ~Asset();

        AssetDescriptor Descript();
    protected:
        AAsset* mAsset;
        char* mBuffer;
    };
}

#endif

#endif
