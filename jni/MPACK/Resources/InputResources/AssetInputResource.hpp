#ifdef ANDROID_PLATFORM

#ifndef MPACK_ASSETINPUTRESOURCE_HPP
#define MPACK_ASSETINPUTRESOURCE_HPP

#include "InputResource.hpp"
#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		struct AssetInputResourceDescriptor
		{
			int32_t mDescriptor;
			off_t mStart;
			off_t mLength;
		};

		class AssetInputResource : public InputResource
		{
		public:
			AssetInputResource(const char* pPath);

			virtual ReturnValue Open();
			virtual void Close();

			virtual ReturnValue Read(void* pBuffer, size_t count);
			virtual ReturnValue ReadFrom(int offset, void* pBuffer, size_t count);
			virtual const void* Bufferize();

			virtual int GetOffset();
			virtual void SetOffset(int offset);
			virtual void Skip(int bytes);

			virtual int GetLength();

			virtual ~AssetInputResource();

			AssetInputResourceDescriptor Descript();
		protected:
			AAsset* mAsset;
			char* mBuffer;
		};
	}
}

#endif

#endif
