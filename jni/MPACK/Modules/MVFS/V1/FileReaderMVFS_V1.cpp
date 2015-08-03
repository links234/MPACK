#include "FileReaderMVFS_V1.hpp"

#include "MVFSNode.hpp"
#include "MVFSReader.hpp"
#include "FileReaderInterface.hpp"

#include <iostream>

using namespace std;

namespace MVFS
{
    namespace V1
    {
        FileReaderMVFS::FileReaderMVFS()
            : m_pNode(NULL), m_offset(0)
        {
        }

        FileReaderMVFS::~FileReaderMVFS()
        {
        }

        int FileReaderMVFS::Size()
        {
            return m_pNode->GetFileSize();
        }

        void FileReaderMVFS::Reset()
        {
            m_offset=0;
        }

        void FileReaderMVFS::Read(char *pBuffer, int size)
        {
            ReadFrom(m_offset,pBuffer,size);
            m_offset+=size;
        }

        void FileReaderMVFS::ReadFrom(int offset, char *pBuffer, int size)
        {
            m_pNode->m_pReader->m_pFileReaderItf->ReadFrom(m_pNode->m_fileOffset+offset,pBuffer,size);

            vector<char> &key=m_pNode->m_pReader->m_key;

            if(key.size())
            {
                int keyIndex=offset%key.size();

                for(int i=0;i<size;++i)
                {
                    pBuffer[i]^=key[keyIndex];

                    ++keyIndex;
                    if(keyIndex>=key.size())
                    {
                        keyIndex=0;
                    }
                }
            }
        }

        void FileReaderMVFS::Skip(int size)
        {
            m_offset+=size;
        }

        int FileReaderMVFS::GetOffset()
        {
            return m_offset;
        }

        void FileReaderMVFS::SetOffset(int offset)
        {
            m_offset=offset;
        }

        FileReaderMVFS* FileReaderMVFS::Open(MVFS::Node *pNode)
        {
            if(pNode == NULL)
            {
                // Error: pNode is NULL
                return NULL;
            }
            if(pNode == MVFS::Node::GetSentinel())
            {
                // Error: pNode is not valid (sentinel)
                return NULL;
            }
            if(!pNode->IsFile())
            {
                // Error: pNode is not valid (not a file)
                return NULL;
            }
            FileReaderMVFS *pReader = new FileReaderMVFS();
            pReader->m_pNode=pNode;
            return pReader;
        }
    }
}
