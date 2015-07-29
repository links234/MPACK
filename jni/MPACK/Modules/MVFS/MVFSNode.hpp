#ifndef MVFSNODE_HPP
#define MVFSNODE_HPP

#include <unordered_map>
#include <string>

namespace MVFS
{
    class Reader;
    class FileReaderInterface;

    namespace V1
    {
        class Reader;
        class FileReaderMVFS;
    }
}

namespace MVFS
{
    class Node
    {
    public:
        ~Node();

        enum Type{DIR,FILE};

        std::unordered_map<std::string,Node*>& GetDirectories();
        std::unordered_map<std::string,Node*>& GetFiles();
        Node* Get(std::string name);

        Type GetType() const;
        bool IsDirectory() const;
        bool IsFile() const;

        Node* GetParent() const;
        int GetFileSize() const;
        int GetFileOffset() const;

        FileReaderInterface* Open();

        static Node* GetSentinel();

    private:
        Node(Reader *reader, Type type);

        void SetParent(Node *parent);

        std::unordered_map<std::string,Node*> m_directories, m_files;
        Type m_type;
        int m_fileOffset;
        int m_fileSize;

        Reader *m_pReader;
        Node *m_pParent;

        static Node s_sentinel;

        friend class MVFS::Reader;
        friend class MVFS::V1::Reader;
        friend class MVFS::V1::FileReaderMVFS;
    };
}

#endif
