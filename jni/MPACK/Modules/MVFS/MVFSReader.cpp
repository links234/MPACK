#include "MVFSReader.hpp"

#include <cstddef>

#include "FileReaderInterface.hpp"
#include "MVFS_V1_Reader.hpp"
#include "MVFSNode.hpp"

#include <iostream>
using namespace std;

namespace MVFS
{
    Reader::Reader(FileReaderInterface *pFileReaderItf, std::vector<char> key)
        : m_pFileReaderItf(pFileReaderItf), m_version(0), m_key(key), m_pRoot(0)
    {
    }

    Reader::~Reader()
    {
        delete m_pRoot;
    }

    Reader* Reader::Open(FileReaderInterface *pFileReaderItf, std::vector<char> key)
    {
        unsigned char version = ReadVersion(pFileReaderItf);
        if(version == 1)
        {
            pFileReaderItf->Reset();
            return new V1::Reader(pFileReaderItf,key);
        }
        //SHOULD PRINT ERROR HERE!!
        return NULL;
    }

    unsigned char Reader::ReadVersion(FileReaderInterface *pFileReaderItf)
    {
        unsigned char version = 0;
        pFileReaderItf->ReadFrom(0,(char*)(&version),1);
        return (version>>4);
    }

    unsigned char Reader::GetVersion()
    {
        return (m_version>>4);
    }

    Node* Reader::GetRoot()
    {
        return m_pRoot;
    }
}
