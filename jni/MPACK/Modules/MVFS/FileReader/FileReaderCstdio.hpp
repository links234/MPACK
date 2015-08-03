#ifndef MVFS_FILEREADERCSTDIO_HPP
#define MVFS_FILEREADERCSTDIO_HPP

#include <cstdio>

#include "FileReaderInterface.hpp"

namespace MVFS
{
    class FileReaderCstdio : public FileReaderInterface
    {
    public:
        virtual ~FileReaderCstdio();

        virtual int Size();
        virtual void Reset();

        virtual void Read(char *pBuffer, int size);
        virtual void ReadFrom(int offset, char *pBuffer, int size);

        virtual void Skip(int size);
        virtual int GetOffset();
        virtual void SetOffset(int offset);

        static FileReaderCstdio* Open(const char *pPath);

    protected:
        FileReaderCstdio(const char *pPath);

        void Init(const char *pPath);
        void Uninit();

        FILE *m_file;
        int m_offset;
        int m_size;
    };
}

#endif
