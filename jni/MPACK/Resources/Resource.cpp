#include "Resource.hpp"
#include "Asset.hpp"
#include "SDInputFile.hpp"

namespace MPACK
{
	namespace Core
	{
		const int PATH_BUFFER_SIZE=256;

		Resource::Resource(const char* pPath)
		{
			LOGD("%s = %d",pPath,strlen(pPath));
			mPath = new char[strlen(pPath)+2];
			strcpy(mPath,pPath);
		}

		const char* Resource::GetPath()
		{
			return mPath;
		}

		Resource::~Resource()
		{
			delete[] mPath;
		}

		Resource* LoadResource(const char* pPath)
		{
	#ifdef ANDROID_PLATFORM
			if(pPath[0]=='@')
			{
				return (Resource*)(new Asset(pPath+1));
			}
			if(pPath[1]=='&')
			{
				return (Resource*)(new SDInputFile(pPath+1));
			}
	#elif	defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
			char pathBuffer[PATH_BUFFER_SIZE];
			if(pPath[0]=='@')
			{
				strcpy(pathBuffer,"assets/");
				strcat(pathBuffer,pPath+1);
			}
			if(pPath[1]=='&')
			{
				strcpy(pathBuffer,pPath+1);
			}
			LOGI("LoadResource:");
			LOGI("%s", pPath);
			LOGI("%s", pathBuffer);
			return (Resource*)(new SDInputFile(pathBuffer));
	#endif
			LOGE("LoadResource: invalid path %s",pPath);
			return NULL;
		}
	}
}
