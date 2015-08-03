#ifndef MVFS_MVFSREADER_HPP
#define MVFS_MVFSREADER_HPP

#include <vector>

namespace MVFS
{
    class FileReaderInterface;

    class Node;

    namespace V1
    {
        class FileReaderMVFS;
    }
}

namespace MVFS
{
    class Reader
    {
    public:
        virtual ~Reader();

        static Reader* Open(FileReaderInterface *pFileReaderItf, std::vector<char> key);

        unsigned char GetVersion();
        virtual FileReaderInterface* Open(Node *pNode) = 0;

        Node* GetRoot();

    protected:
        Reader(FileReaderInterface *pReaderItf, std::vector<char> key);

        static unsigned char ReadVersion(FileReaderInterface *pFileReaderItf);

        FileReaderInterface *m_pFileReaderItf;
        Node *m_pRoot;
        unsigned char m_version;
        std::vector<char> m_key;

        friend class MVFS::V1::FileReaderMVFS;
    };
}

#endif
