#include "Resource.hpp"

#include "Asset.hpp"
#include "SDInputFile.hpp"
#include "StringEx.hpp"

using namespace std;

namespace MPACK
{
	namespace Core
	{
		const int PATH_BUFFER_SIZE=256;

		Resource::Resource(const char* pPath)
		{
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
			if(pPath[0]=='&')
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
			if(pPath[0]=='&')
			{
				strcpy(pathBuffer,pPath+1);
			}
			return (Resource*)(new SDInputFile(pathBuffer));
	#endif
			LOGE("LoadResource: invalid path %s",pPath);
			return NULL;
		}

		string GetResourcePath(string path)
		{
	#ifdef ANDROID_PLATFORM
			if(path[0]=='@')
			{
				return StringEx::Substring(path,1);
			}
			if(path[0]=='&')
			{
				return StringEx::Substring(path,1);
			}
	#elif	defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
			if(pPath[0]=='@')
			{
				return string("assets/")+StringEx::Substring(path,1);
			}
			if(pPath[0]=='&')
			{
				return StringEx::Substring(path,1);
			}
	#endif
			return path;
		}
	}
}
