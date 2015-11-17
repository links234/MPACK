#ifndef MPACK_FILEINPUTRESOURCE_HPP
#define MPACK_FILEINPUTRESOURCE_HPP

#include "InputResource.hpp"
#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class FileInputResource : public InputResource
		{
		public:
			FileInputResource(const char* pPath);

			virtual ReturnValue Open();
			virtual void Close();

			virtual ReturnValue Read(void* pBuffer, size_t count);
			virtual ReturnValue ReadFrom(int offset, void* pBuffer, size_t count);
			virtual const void* Bufferize();

			virtual int GetOffset();
			virtual void SetOffset(int offset);
			virtual void Skip(int bytes);

			virtual int GetLength();

			virtual ~FileInputResource();
		protected:
			std::ifstream mInputStream;
			char* mBuffer;
		};
	}
}

#endif
