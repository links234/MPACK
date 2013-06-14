#include "SDInputFile.hpp"
#include "Log.hpp"

#include <sys/stat.h>

namespace Core
{
    SDInputFile::SDInputFile(const char* pPath):
        Resource(pPath), mInputStream(), mBuffer(NULL)
    {
    }

    Status SDInputFile::Open()
    {
        mInputStream.open(mPath, std::ios::in | std::ios::binary);
        if(mInputStream)
        {
        	LOGE("Failed to open SD file: %s",mPath);
        }
        return mInputStream ? STATUS_OK : STATUS_KO;
    }

    void SDInputFile::Close()
	{
    	if(mInputStream.is_open())
    	{
    		mInputStream.close();
    	}
    	if(!mBuffer)
    	{
    		delete[] mBuffer;
    		mBuffer = NULL;
    	}
	}

    Status SDInputFile::Read(void* pBuffer, size_t pCount)
    {
        mInputStream.read((char*)pBuffer, pCount);
        return (!mInputStream.fail()) ? STATUS_OK : STATUS_KO;
    }

    off_t SDInputFile::GetLength()
    {
        struct stat filestatus;
        if (stat(mPath, &filestatus) >= 0)
        {
            return filestatus.st_size;
        }
        else
        {
            return -1;
        }
    }

    const void* SDInputFile::Bufferize()
    {
        off_t lSize = GetLength();
        if (lSize <= 0) return NULL;

        mBuffer = new char[lSize];
        mInputStream.read(mBuffer, lSize);
        if (!mInputStream.fail())
        {
            return mBuffer;
        }
        else
        {
            return NULL;
        }
    }

    SDInputFile::~SDInputFile()
    {
    	Close();
    }
}
