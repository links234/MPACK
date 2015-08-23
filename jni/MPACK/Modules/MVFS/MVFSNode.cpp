#include "MVFSNode.hpp"

#include "MVFSReader.hpp"

#include <iostream>

using namespace std;

namespace MVFS
{
    Node Node::s_sentinel(NULL, Node::DIR);

    Node::Node(Reader *reader, Node::Type type)
        : m_type(type), m_fileOffset(0), m_fileSize(0), m_pReader(reader), m_pParent(&s_sentinel)
    {
        m_directories.clear();
        m_files.clear();
    }

    Node::~Node()
    {
        for(unordered_map<string,Node*>::iterator it=m_directories.begin();it!=m_directories.end();++it)
        {
            delete it->second;
        }
        for(unordered_map<string,Node*>::iterator it=m_files.begin();it!=m_files.end();++it)
        {
            delete it->second;
        }
    }

    unordered_map<string,Node*>& Node::GetDirectories()
    {
        return m_directories;
    }

    unordered_map<string,Node*>& Node::GetFiles()
    {
        return m_files;
    }

    Node* Node::Get(std::string name)
    {
        unordered_map<string,Node*>::iterator it=m_directories.find(name);
        if(it!=m_directories.end())
        {
            return it->second;
        }
        it=m_files.find(name);
        if(it!=m_files.end())
        {
            return it->second;
        }
        return &s_sentinel;
    }

    Node::Type Node::GetType() const
    {
        return m_type;
    }

    bool Node::IsDirectory() const
    {
        return m_type == Node::DIR;
    }

    bool Node::IsFile() const
    {
        return m_type == Node::FILE;
    }

    Reader* Node::GetReader() const
    {
        return m_pReader;
    }

    Node* Node::GetParent() const
    {
        return m_pParent;
    }

    int Node::GetFileSize() const
    {
        return m_fileSize;
    }

    int Node::GetFileOffset() const
    {
        return m_fileOffset;
    }

    FileReaderInterface* Node::Open()
    {
        return m_pReader->Open(this);
    }

    Node* Node::GetSentinel()
    {
        return &s_sentinel;
    }

    void Node::SetParent(Node *parent)
    {
        m_pParent=parent;
    }
}
