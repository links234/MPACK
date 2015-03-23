#ifndef MPACK_RESOURCE_HPP
#define MPACK_RESOURCE_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class Resource
		{
		public:
			Resource(const char* pPath);
			virtual ~Resource();

			const char* GetPath();

			virtual ReturnValue Open() = 0;
			virtual void Close() = 0;
			virtual ReturnValue Read(void* pBuffer, size_t pCount) = 0;

			virtual int GetLength() = 0;
			virtual const void* Bufferize() = 0;
		protected:
			char* 	mPath;
		};

		Resource* LoadResource(const char* pPath);
		std::string GetResourcePath(std::string path);
	}
}

#endif
