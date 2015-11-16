#include "FileReaderMPACK.hpp"

#include "InputResource.hpp"

namespace MVFS
{
	FileReaderMPACK::FileReaderMPACK(const char *pPath)
	{
		m_pInputResource = MPACK::Core::GetInputResource(pPath);
		m_pInputResource->Open();
	}

	FileReaderMPACK::~FileReaderMPACK()
	{
		delete m_pInputResource;
	}

	int FileReaderMPACK::Size()
	{
		return m_pInputResource->GetLength();
	}

	void FileReaderMPACK::Reset()
	{
		m_pInputResource->SetOffset(0);
	}

	void FileReaderMPACK::Read(char *pBuffer, int size)
	{
		m_pInputResource->Read(pBuffer,size);
	}

	void FileReaderMPACK::ReadFrom(int offset, char *pBuffer, int size)
	{
		m_pInputResource->ReadFrom(offset,pBuffer,size);
	}

	void FileReaderMPACK::Skip(int size)
	{
		m_pInputResource->Skip(size);
	}

	int FileReaderMPACK::GetOffset()
	{
		return m_pInputResource->GetOffset();
	}

	void FileReaderMPACK::SetOffset(int offset)
	{
		m_pInputResource->SetOffset(offset);
	}

	FileReaderMPACK* FileReaderMPACK::Open(const char *pPath)
	{
		return new FileReaderMPACK(pPath);
	}
}
