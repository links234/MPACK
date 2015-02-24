#ifndef MPACK_SDINPUTFILE_HPP
#define MPACK_SDINPUTFILE_HPP

#include "Resource.hpp"
#include "Types.hpp"

#include <fstream>

namespace MPACK
{
	namespace Core
	{
		class SDInputFile : public Resource
		{
		public:
			SDInputFile(const char* pPath);

			virtual ReturnValue Open();
			virtual void Close();
			virtual ReturnValue Read(void* pBuffer, size_t pCount);

			virtual int GetLength();
			virtual const void* Bufferize();

			virtual ~SDInputFile();
		protected:
			std::ifstream mInputStream;
			char* mBuffer;
		};
	}
}

#endif
