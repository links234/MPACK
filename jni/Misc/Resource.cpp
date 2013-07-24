#include "Resource.hpp"
#include "Asset.hpp"
#include "SDInputFile.hpp"

namespace Core
{
	const int PATH_BUFFER_SIZE=256;

    Resource::Resource(const char* pPath)
    {
    	LOGD("%s = %d",pPath,strlen(pPath)+2);
    	mPath = new char[strlen(pPath)+2];
    	LOGD("test");
    	strcpy(mPath,pPath);
    	LOGD("test2");
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
#elif	defined(WINDOWS_PLATFORM)
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
		MessageBox(NULL,"LoadResource:","Fatal error",MB_OK);
		MessageBox(NULL,pPath,"Fatal error",MB_OK);
		MessageBox(NULL,pathBuffer,"Fatal error",MB_OK);
		return (Resource*)(new SDInputFile(pathBuffer));
#endif
    	LOGE("LoadResource: invalid path %s",pPath);
    	return NULL;
    }
}
