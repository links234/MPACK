#include "Resource.hpp"
#include "Asset.hpp"
#include "SDInputFile.hpp"

namespace Core
{
    Resource::Resource(const char* pPath):
        mPath(pPath)
    {
    }

    const char* Resource::GetPath()
    {
        return mPath;
    }

    Resource::~Resource()
    {
    }

    Resource* LoadResource(const char* pPath)
    {
    	if(pPath[0]=='@')
    	{
    		return (Resource*)(new Asset(pPath+1));
    	}
    	if(pPath[1]=='&')
    	{
    		return (Resource*)(new SDInputFile(pPath+1));
    	}
    	LOGE("LoadResource: invalid path %s",pPath);
    	return NULL;
    }
}
