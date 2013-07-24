#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "Types.hpp"

namespace Core
{
    class Resource
    {
    public:
        Resource(const char* pPath);
        virtual ~Resource();

        const char* GetPath();

        virtual Status Open() = 0;
        virtual void Close() = 0;
        virtual Status Read(void* pBuffer, size_t pCount) = 0;

        virtual int GetLength() = 0;
        virtual const void* Bufferize() = 0;
    protected:
        char* 	mPath;
    };

    Resource* LoadResource(const char* pPath);
}
#endif
