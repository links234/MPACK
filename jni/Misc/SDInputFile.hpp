#ifndef SDINPUTFILE_HPP
#define SDINPUTFILE_HPP

#include "Resource.hpp"
#include "Types.hpp"

#include <fstream>

namespace Core
{
    class SDInputFile : public Resource
    {
    public:
        SDInputFile(const char* pPath);

        virtual Status Open();
        virtual void Close();
        virtual Status Read(void* pBuffer, size_t pCount);

        virtual int GetLength();
        virtual const void* Bufferize();

        virtual ~SDInputFile();
    protected:
        std::ifstream mInputStream;
        char* mBuffer;
    };
}
#endif
