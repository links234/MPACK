#include "Global.hpp"

#include "Context.hpp"

namespace Global
{
	android_app 			*pAndroidApp=NULL;
	AAssetManager 			*pAAssetManager=NULL;
	Core::Context			*pContext=NULL;
	Core::EventLoop			*pEventLoop;

	TextureMappedFont		*pFont;

	Camera2D				*pActiveCamera;
}

