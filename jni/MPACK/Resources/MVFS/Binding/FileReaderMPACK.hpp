#ifndef MPACK_FILEREADERMPACK_HPP
#define MPACK_FILEREADERMPACK_HPP

#include "FileReaderInterface.hpp"

namespace MPACK
{
	namespace Core
	{
		class InputResource;
	}
}

namespace MVFS
{
	class FileReaderMPACK : public MVFS::FileReaderInterface
	{
	public:
		virtual ~FileReaderMPACK();

		virtual int Size();
		virtual void Reset();

		virtual void Read(char *pBuffer, int size);
		virtual void ReadFrom(int offset, char *pBuffer, int size);

		virtual void Skip(int size);
		virtual int GetOffset();
		virtual void SetOffset(int offset);

		static FileReaderMPACK* Open(const char *pPath);

	protected:
		FileReaderMPACK(const char *pPath);

		MPACK::Core::InputResource *m_pInputResource;
	};
}

#endif
