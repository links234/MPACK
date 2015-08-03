#ifndef MPACK_MVFSINPUTFILE_HPP
#define MPACK_MVFSINPUTFILE_HPP

#include "Resource.hpp"
#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class MVFSInputFile : public Resource
		{
		public:
			MVFSInputFile(const char* pPath);

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

		};
	}
}

#endif
