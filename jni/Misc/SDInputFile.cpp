#include "SDInputFile.hpp"
#include "Log.hpp"

namespace Core
{
    SDInputFile::SDInputFile(const char* pPath):
        Resource(pPath), mInputStream(), mBuffer(NULL)
    {
    	LOGD("Test3");
    }

    Status SDInputFile::Open()
    {
    	LOGD("Test4 |%s| ",mPath);
        mInputStream.open(mPath, std::ios::in | std::ios::binary);
        LOGD("Test5");
        if(mInputStream)
        {
        	LOGD("ADASDASJDASKHDASKH");
        	LOGD("Failed to open SD file: |%s|",mPath);
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

    int SDInputFile::GetLength()
    {
    	LOGD("%s",mPath);
    	std::ifstream file( mPath, std::ios::binary | std::ios::ate);
    	return (int)file.tellg();
    }

    const void* SDInputFile::Bufferize()
    {
        int lSize = GetLength();
        LOGD("lSize = %d",lSize);
        if (lSize <= 0)
        {
        	MessageBox(NULL,"GetLength()==NULL ....","Fatal error",MB_OK);
        	return NULL;
        }

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
