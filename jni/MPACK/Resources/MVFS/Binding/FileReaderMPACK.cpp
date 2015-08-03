#include "FileReaderMPACK.hpp"

namespace MVFS
{
	FileReaderMPACK::FileReaderMPACK(const char *pPath)
	{
		m_pResource = new MPACK::Core::Resource(pPath);
	}

	FileReaderMPACK::~FileReaderMPACK()
	{
		delete m_pResource;
	}

	int FileReaderMPACK::Size()
	{
		return m_pResource->GetLength();
	}

	void FileReaderMPACK::Reset()
	{
		m_pResource->SetOffset(0);
	}

	void FileReaderMPACK::Read(char *pBuffer, int size)
	{
		m_pResource->Read(pBuffer,size);
	}

	void FileReaderMPACK::ReadFrom(int offset, char *pBuffer, int size)
	{
		m_pResource->ReadFrom(offset,pBuffer,size);
	}

	void FileReaderMPACK::Skip(int size)
	{
		m_pResource->Skip(size);
	}

	int FileReaderMPACK::GetOffset()
	{
		return m_pResource->GetOffset();
	}

	FileReaderMPACK* FileReaderMPACK::Open(const char *pPath)
	{
		return new FileReaderMPACK(pPath);
	}
}
