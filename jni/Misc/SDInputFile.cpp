#include "SDInputFile.hpp"
#include "Log.hpp"

namespace Core
{
    SDInputFile::SDInputFile(const char* pPath):
        Resource(pPath), mInputStream(), mBuffer(NULL)
    {
    	LOGD("SDInputFile constructor");
    }

    ReturnValue SDInputFile::Open()
    {
    	LOGD("SDInputFile Opening |%s| ",mPath);
        mInputStream.open(mPath, std::ios::in | std::ios::binary);
        if(mInputStream.fail())
        {
        	LOGD("Failed to open SD file: |%s|",mPath);
        }
        else
        {
        	LOGD("Successfully opened SD file");
        }
        return mInputStream ? RETURN_VALUE_OK : RETURN_VALUE_KO;
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

    ReturnValue SDInputFile::Read(void* pBuffer, size_t pCount)
    {
        mInputStream.read((char*)pBuffer, pCount);
        return (!mInputStream.fail()) ? RETURN_VALUE_OK : RETURN_VALUE_KO;
    }

    int SDInputFile::GetLength()
    {
    	int len;
    	LOGD("getting size of %s",mPath);

    	if(mInputStream.is_open())
    	{
    		int pos = mInputStream.tellg();
    		mInputStream.seekg(0, mInputStream.end);
    		len = mInputStream.tellg();
    		mInputStream.seekg(pos);
    	}
    	else
    	{
    		std::ifstream file( mPath, std::ios::binary | std::ios::ate);
			len = file.tellg();
			file.close();
    	}

    	return len;
    }

    const void* SDInputFile::Bufferize()
    {
        int lSize = GetLength();
        LOGD("lSize = %d",lSize);
        if (lSize <= 0)
        {
        	return NULL;
        }

        if(mBuffer != NULL)
        {
        	LOGI("Already bufferized");
        	return mBuffer;
        }
        mBuffer = new char[lSize+1];

        int pos = mInputStream.tellg();
        mInputStream.seekg(0);
        mInputStream.read(mBuffer, lSize);
        mInputStream.seekg(pos);

        mBuffer[lSize]=NULL;

        if (!mInputStream.fail())
        {
            return mBuffer;
        }
        else
        {
        	LOGE("Bufferize failed for SDInputFile %s", mPath);
            return NULL;
        }
    }

    SDInputFile::~SDInputFile()
    {
    	Close();
    }
}
