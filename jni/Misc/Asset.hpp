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

        virtual ReturnValue Open();
        virtual void Close();
        virtual ReturnValue Read(void* pBuffer, size_t pCount);

        virtual int GetLength();
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
