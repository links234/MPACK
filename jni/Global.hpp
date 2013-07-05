#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "Types.hpp"
#include "Context.hpp"
#include "TextureMappedFont.hpp"
#include "EventLoop.hpp"

#define HUD_LAYER		500.0f

namespace Global
{
	extern android_app 				*pAndroidApp;
	extern AAssetManager 			*pAAssetManager;
	extern Core::Context			*pContext;
	extern Core::EventLoop			*pEventLoop;

	extern TextureMappedFont	*pFont;
}

#endif
