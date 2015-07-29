#ifndef FILEREADERMVFS_V1_HPP
#define FILEREADERMVFS_V1_HPP

#include "FileReaderInterface.hpp"
#include "FileReaderCstdio.hpp"

namespace MVFS
{
    class Node;
}

namespace MVFS
{
    namespace V1
    {
        class FileReaderMVFS
        {
        public:
            virtual ~FileReaderMVFS();

            virtual int Size();
            virtual void Reset();

            virtual void Read(char *pBuffer, int size);
            virtual void ReadFrom(int offset, char *pBuffer, int size);

            virtual void Skip(int size);
            virtual int GetOffset();

            static FileReaderMVFS* Open(MVFS::Node *pNode);

        protected:
            FileReaderMVFS();

            MVFS::Node *m_pNode;
            int m_offset;
        };
    }
}

#endif
