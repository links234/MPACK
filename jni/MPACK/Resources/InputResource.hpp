#ifndef MPACK_INPUTINPUTRESOURCE_HPP
#define MPACK_INPUTINPUTRESOURCE_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class InputResource
		{
		public:
			InputResource(const char* pPath);
			virtual ~InputResource();

			const char* GetPath();

			virtual ReturnValue Open() = 0;
			virtual void Close() = 0;

			virtual ReturnValue Read(void* pBuffer, size_t count) = 0;
			virtual ReturnValue ReadFrom(int offset, void* pBuffer, size_t count) = 0;
			virtual const void* Bufferize() = 0;

			virtual int GetOffset() = 0;
			virtual void SetOffset(int offset) = 0;
			virtual void Skip(int bytes) = 0;

			virtual int GetLength() = 0;
		protected:
			char* 	mPath;
		};

		InputResource* GetInputResource(const char* pPath);
		std::string GetInputResourcePath(std::string path);
	}
}

#endif
