#include "FileInputResource.hpp"
#include "Log.hpp"

namespace MPACK
{
	namespace Core
	{
		FileInputResource::FileInputResource(const char* pPath):
			InputResource(pPath), mInputStream(), mBuffer(NULL)
		{
		}

		ReturnValue FileInputResource::Open()
		{
			mInputStream.open(mPath, std::ios::in | std::ios::binary);
			return mInputStream ? RETURN_VALUE_OK : RETURN_VALUE_KO;
		}

		void FileInputResource::Close()
		{
			if(mInputStream.is_open())
			{
				mInputStream.close();
			}
			if(mBuffer)
			{
				delete[] mBuffer;
				mBuffer = NULL;
			}
		}

		ReturnValue FileInputResource::Read(void* pBuffer, size_t count)
		{
			mInputStream.read((char*)pBuffer, count);
			return (!mInputStream.fail()) ? RETURN_VALUE_OK : RETURN_VALUE_KO;
		}

		ReturnValue FileInputResource::ReadFrom(int offset, void* pBuffer, size_t count)
		{
			if(mInputStream.is_open())
			{
				int oldOffset=GetOffset();
				SetOffset(offset);
				Read(pBuffer,count);
				SetOffset(oldOffset);
			}
		}

		const void* FileInputResource::Bufferize()
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
				LOGE("Bufferize failed for FileInputResource %s", mPath);
				return NULL;
			}
		}

		int FileInputResource::GetOffset()
		{
			if(mInputStream.is_open())
			{
				int offset=mInputStream.tellg();
				if(offset < -1)
				{
					LOGE("FileInputResource::GetOffset error: tellg() returned -1 yet file is still opened!");
				}
				return offset;
			}
			else
			{
				return 0;
			}
		}

		void FileInputResource::SetOffset(int offset)
		{
			if(mInputStream.is_open())
			{
				mInputStream.seekg(offset, mInputStream.beg);
			}
		}

		void FileInputResource::Skip(int bytes)
		{
			if(mInputStream.is_open())
			{
				int offset=GetOffset();
				SetOffset(offset+bytes);
			}
		}

		int FileInputResource::GetLength()
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

		FileInputResource::~FileInputResource()
		{
			Close();
		}
	}
}
