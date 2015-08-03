#include "SDInputFile.hpp"
#include "Log.hpp"

namespace MPACK
{
	namespace Core
	{
		SDInputFile::SDInputFile(const char* pPath):
			Resource(pPath), mInputStream(), mBuffer(NULL)
		{
		}

		ReturnValue SDInputFile::Open()
		{
			mInputStream.open(mPath, std::ios::in | std::ios::binary);
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

		ReturnValue SDInputFile::Read(void* pBuffer, size_t count)
		{
			mInputStream.read((char*)pBuffer, pCount);
			return (!mInputStream.fail()) ? RETURN_VALUE_OK : RETURN_VALUE_KO;
		}

		ReturnValue SDInputFile::ReadFrom(int offset, void* pBuffer, size_t count)
		{
			if(mInputStream.is_open())
			{
				int oldOffset=GetOffset();
				SetOffset(offset);
				Read(pBuffer,count);
				SetOffset(oldOffset);
			}
		}

		const void* SDInputFile::Bufferize()
		{
			int lSize = GetLength();
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

			mBuffer[lSize]=0;

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

		int SDInputFile::GetOffset()
		{
			if(mInputStream.is_open())
			{
				int offset=mInputStream.tellg();
				if(offset < -1)
				{
					LOGE("SDInputFile::GetOffset error: tellg() returned -1 yet file is still opened!");
				}
				return offset;
			}
			else
			{
				return 0;
			}
		}

		void SDInputFile::SetOffset(int offset)
		{
			if(mInputStream.is_open())
			{
				mInputStream.seekg(offset, mInputStream.beg());
			}
		}

		void SDInputFile::Skip(int bytes)
		{
			if(mInputStream.is_open())
			{
				int offset=GetOffset();
				SetOffset(offset+bytes);
			}
		}

		int SDInputFile::GetLength()
		{
			int len;

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

		SDInputFile::~SDInputFile()
		{
			Close();
		}
	}
}
