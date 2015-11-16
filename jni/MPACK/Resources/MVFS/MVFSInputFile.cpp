#include "MVFSInputFile.hpp"

#include "Types.hpp"

#include "FileReaderInterface.hpp"

namespace MPACK
{
	namespace Core
	{
		MVFSInputFile::MVFSInputFile(MVFS::FileReaderInterface *pFileReader, bool autoDeletePointers)
			: InputResource("File is inside MVFS"), m_pFileReader(pFileReader),
			  m_autoDeletePointers(autoDeletePointers), m_pBuffer(NULL)
		{
		}

		MVFSInputFile::~MVFSInputFile()
		{
			Close();

			if(m_autoDeletePointers)
			{
				delete m_pFileReader;
			}
		}

		ReturnValue MVFSInputFile::Open()
		{
			return RETURN_VALUE_OK;
		}

		void MVFSInputFile::Close()
		{
			if(m_pBuffer)
			{
				delete[] m_pBuffer;
				m_pBuffer = NULL;
			}
		}

		ReturnValue MVFSInputFile::Read(void* pBuffer, size_t count)
		{
			m_pFileReader->Read((char*)pBuffer,count);
			return RETURN_VALUE_OK;
		}

		ReturnValue MVFSInputFile::ReadFrom(int offset, void* pBuffer, size_t count)
		{
			m_pFileReader->ReadFrom(offset, (char*)pBuffer, count);
			return RETURN_VALUE_OK;
		}

		const void* MVFSInputFile::Bufferize()
		{
			int size = GetLength();
			if (size <= 0)
			{
				return NULL;
			}

			if(m_pBuffer != NULL)
			{
				LOGI("Already bufferized");
				return m_pBuffer;
			}

			m_pBuffer = new char[size+1];
			m_pFileReader->ReadFrom(0,m_pBuffer,size);
			m_pBuffer[size]=0;

			return m_pBuffer;
		}

		int MVFSInputFile::GetOffset()
		{
			return m_pFileReader->GetOffset();
		}

		void MVFSInputFile::SetOffset(int offset)
		{
			m_pFileReader->SetOffset(offset);
		}

		void MVFSInputFile::Skip(int bytes)
		{
			m_pFileReader->Skip(bytes);
		}

		int MVFSInputFile::GetLength()
		{
			return m_pFileReader->Size();
		}
	}
}
