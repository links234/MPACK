#include "MVFS_V1_Reader.hpp"

#include <iostream>

#include "MVFS_V1_Constants.hpp"
#include "FileReaderInterface.hpp"
#include "FileReaderMVFS_V1.hpp"
#include "MVFSNode.hpp"

using namespace std;

namespace MVFS
{
    namespace V1
    {
        Reader::Reader(FileReaderInterface *pFileReaderItf, std::vector<char> key)
            : MVFS::Reader(pFileReaderItf, key)
        {
            m_pFileReaderItf->Read((char*)&m_version,1);

            string name="";
            Node *cursor = m_pRoot = new Node(this, MVFS::Node::DIR);
            Node *fileNode = MVFS::Node::GetSentinel();
            cursor->SetParent(cursor);
            Node *lastMkDir = NULL;

            while(m_pFileReaderItf->GetOffset()<m_pFileReaderItf->Size())
            {
                unsigned char op=0;
                int fileSize;
                std::string name;
                m_pFileReaderItf->Read((char*)&op,1);

                switch(op)
                {
                    case MKDIR:
                        name = ReadString(m_pFileReaderItf);
                        lastMkDir = cursor->m_directories[name] = new Node(this, MVFS::Node::DIR);
                        lastMkDir->SetParent(cursor);
                    break;
                    case OPENDIR:
                        name = ReadString(m_pFileReaderItf);
                        cursor = cursor->Get(name);
                        if(cursor==MVFS::Node::GetSentinel())
                        {
                            cerr<<"ERROR: Directory does not exists!"<<endl;
                        }
                    break;
                    case BACK:
                        cursor=cursor->m_pParent;
                    break;
                    case NEWFILE:
                        name = ReadString(m_pFileReaderItf);
                        fileNode = new Node(this, MVFS::Node::FILE);
                        fileNode->SetParent(cursor);
                        cursor->m_files[name]=fileNode;
                        m_pFileReaderItf->Read((char*)(&fileSize),sizeof(fileSize));
                        fileNode->m_fileSize=fileSize;
                        fileNode->m_fileOffset=m_pFileReaderItf->GetOffset();
                        m_pFileReaderItf->Skip(fileSize);
                    break;
                    case OPENLASTMKDIR:
                        if(!lastMkDir)
                        {
                            cerr<<"ERROR: OPENLASTMKDIR with no previous directory"<<endl;
                        }
                        else
                        {
                            cursor = lastMkDir;
                        }
                    break;
                    default:
                        cerr<<"ERROR: Invalid operation!"<<endl;
                    break;
                }
            }
        }

        string Reader::ReadString(FileReaderInterface *pFileReaderItf)
        {
            string ans="";
            char ch=0;
            pFileReaderItf->Read(&ch,1);
            while(ch)
            {
                ans+=ch;
                pFileReaderItf->Read(&ch,1);
            }
            return ans;
        }

        FileReaderInterface* Reader::Open(Node *pNode)
        {
            return (FileReaderInterface*)(MVFS::V1::FileReaderMVFS::Open(pNode));
        }

        Reader::~Reader()
        {
        }
    }
}
