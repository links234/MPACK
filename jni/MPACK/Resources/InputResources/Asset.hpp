#ifdef ANDROID_PLATFORM

#ifndef MPACK_ASSET_HPP
#define MPACK_ASSET_HPP

#include "InputResource.hpp"
#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		struct AssetDescriptor
		{
			int32_t mDescriptor;
			off_t mStart;
			off_t mLength;
		};

		class Asset : public InputResource
		{
		public:
			Asset(const char* pPath);

			virtual ReturnValue Open();
			virtual void Close();

			virtual ReturnValue Read(void* pBuffer, size_t count);
			virtual ReturnValue ReadFrom(int offset, void* pBuffer, size_t count);
			virtual const void* Bufferize();

			virtual int GetOffset();
			virtual void SetOffset(int offset);
			virtual void Skip(int bytes);

			virtual int GetLength();

			virtual ~Asset();

			AssetDescriptor Descript();
		protected:
			AAsset* mAsset;
			char* mBuffer;
		};
	}
}

#endif

#endif
