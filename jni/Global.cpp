#include "Global.hpp"

#include "Platform.hpp"
#include "Context.hpp"

namespace Global
{
#ifdef ANDROID_PLATFORM
	android_app 			*pAndroidApp=NULL;
	AAssetManager 			*pAAssetManager=NULL;
#endif

	Core::Context			*pContext=NULL;
	Core::EventLoop			*pEventLoop;

	TextureMappedFont		*pFont;

	Camera2D				*pActiveCamera;
}

