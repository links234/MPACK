#ifndef MPACK_GLOBAL_HPP
#define MPACK_GLOBAL_HPP

#include "Types.hpp"

#define HUD_LAYER		500.0f

namespace MPACK
{
	namespace Core
	{
		class Context;
		class EventLoop;
	}
	namespace Graphics
	{
		class Camera2D;
		class TextureMappedFont;
	}
}

namespace MPACK
{
	namespace Global
	{
	#ifdef ANDROID_PLATFORM
		extern android_app 					*pAndroidApp;
		extern AAssetManager 				*pAAssetManager;
	#endif

		extern std::vector<std::string>		arguments;

		extern Core::Context				*pContext;
		extern Core::EventLoop				*pEventLoop;

		extern Graphics::TextureMappedFont	*pFont;

		extern Graphics::Camera2D			*pActiveCamera;
	}
}

#endif
