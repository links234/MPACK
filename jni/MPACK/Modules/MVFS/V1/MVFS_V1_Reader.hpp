#ifndef MVFS_MVFS_V1_READER_HPP
#define MVFS_MVFS_V1_READER_HPP

#include <vector>
#include <string>

#include "MVFSReader.hpp"

namespace MVFS
{
    namespace V1
    {
        class Reader : public MVFS::Reader
        {
        public:
            virtual ~Reader();

            FileReaderInterface* Open(Node *pNode);

        protected:
            Reader(FileReaderInterface *pFileReaderItf, std::vector<char> key);

            std::string ReadString(FileReaderInterface *pFileReaderItf);

            friend class MVFS::Reader;
        };
    }
}

#endif
