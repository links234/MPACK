#ifndef MPACK_MVFSINPUTFILE_HPP
#define MPACK_MVFSINPUTFILE_HPP

#include "Types.hpp"
#include "InputResource.hpp"

namespace MVFS
{
	class FileReaderInterface;
}

namespace MPACK
{
	namespace Core
	{
		class MVFSInputFile : public InputResource
		{
		public:
			MVFSInputFile(MVFS::FileReaderInterface *pFileReader, bool autoDeletePointers = false);

			virtual ReturnValue Open();
			virtual void Close();

			virtual ReturnValue Read(void* pBuffer, size_t count);
			virtual ReturnValue ReadFrom(int offset, void* pBuffer, size_t count);
			virtual const void* Bufferize();

			virtual int GetOffset();
			virtual void SetOffset(int offset);
			virtual void Skip(int bytes);

			virtual int GetLength();

			virtual ~MVFSInputFile();

		protected:
			MVFS::FileReaderInterface *m_pFileReader;
			bool m_autoDeletePointers;

			char *m_pBuffer;
		};
	}
}

#endif
