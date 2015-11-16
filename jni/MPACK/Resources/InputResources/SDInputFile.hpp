#ifndef MPACK_SDINPUTFILE_HPP
#define MPACK_SDINPUTFILE_HPP

#include "InputResource.hpp"
#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class SDInputFile : public InputResource
		{
		public:
			SDInputFile(const char* pPath);

			virtual ReturnValue Open();
			virtual void Close();

			virtual ReturnValue Read(void* pBuffer, size_t count);
			virtual ReturnValue ReadFrom(int offset, void* pBuffer, size_t count);
			virtual const void* Bufferize();

			virtual int GetOffset();
			virtual void SetOffset(int offset);
			virtual void Skip(int bytes);

			virtual int GetLength();

			virtual ~SDInputFile();
		protected:
			std::ifstream mInputStream;
			char* mBuffer;
		};
	}
}

#endif
