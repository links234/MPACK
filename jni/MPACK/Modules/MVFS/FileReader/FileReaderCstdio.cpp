#include "FileReaderCstdio.hpp"

#include <cstring>

namespace MVFS
{
    FileReaderCstdio::FileReaderCstdio(const char *pPath)
        : m_file(NULL), m_offset(0), m_size(0)
    {
        Init(pPath);
    }

    FileReaderCstdio::~FileReaderCstdio()
    {
        Uninit();
    }

    int FileReaderCstdio::Size()
    {
        return m_size;
    }

    void FileReaderCstdio::Reset()
    {
        m_offset=0;
    }

    void FileReaderCstdio::Read(char *pBuffer, int size)
    {
        ReadFrom(m_offset,pBuffer,size);
        m_offset+=size;
    }

    void FileReaderCstdio::ReadFrom(int offset, char *pBuffer, int size)
    {
        if(offset>=m_size)
        {
            memset(pBuffer,0,size);
            return;
        }
        fseek(m_file,offset,SEEK_SET);
        if(offset+size>m_size)
        {
            int maxpossible=m_size-offset;
            if(fread(pBuffer,1,maxpossible,m_file)!=maxpossible)
            {
                //ERROR
            }
            memset(pBuffer+maxpossible+1,0,size-maxpossible);
            return;
        }
        if(fread(pBuffer,1,size,m_file)!=size)
        {
            //ERROR
        }
    }

    void FileReaderCstdio::Skip(int size)
    {
        m_offset+=size;
    }

    int FileReaderCstdio::GetOffset()
    {
        return m_offset;
    }

    void FileReaderCstdio::SetOffset(int offset)
    {
        m_offset=offset;
    }

    FileReaderCstdio* FileReaderCstdio::Open(const char *pPath)
    {
        return new FileReaderCstdio(pPath);
    }

    void FileReaderCstdio::Init(const char *pPath)
    {
        if(m_file)
        {
            fclose(m_file);
        }
        m_file = fopen(pPath,"rb");
        fseek(m_file,0,SEEK_END);
        m_size=ftell(m_file);
        fseek(m_file,0,SEEK_SET);
    }

    void FileReaderCstdio::Uninit()
    {
        if(m_file)
        {
            fclose(m_file);
        }
    }
}
