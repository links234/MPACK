#include "GraphicsService.hpp"

#include "Global.hpp"
#include "TimeService.hpp"
#include "Render.hpp"
#include "Texture2D.hpp"
#include "TextureMappedFont.hpp"
#include "Log.hpp"
#include "Particles.hpp"
#include "Context.hpp"
#include "Camera2D.hpp"
#include "Sprite.hpp"
#include "AnimatedSprite.hpp"
#include "ShaderTypes.hpp"
#include "PostEffect.hpp"
#include "Profiler.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Graphics
	{
		GraphicsService::GraphicsService()
		{
			LOGI("Creating GraphicsService.");
		}

		GraphicsService::~GraphicsService()
		{
			LOGI("Destroying GraphicsService.");
		}

		ReturnValue GraphicsService::Start()
		{
			InitTextureSlots();

			Render::Init();
			Render::SetOrthoMode();
			Render::EnableOrthoMode();
			Render::EnableAlphaBlend();

			LoadResources();

			PostEffect::Init(Render::GetScreenWidth(),Render::GetScreenHeight());

			return RETURN_VALUE_OK;
		}

		void GraphicsService::Stop()
		{
			LOGI("Stopping GraphicsService.");

			PostEffect::Shutdown();

			UnloadResources();

			Render::DisableAlphaBlend();
			Render::DisableOrthoMode();
			Render::Uninit();

			Batcher::Cleanup();
		}

		void GraphicsService::Update(GLfloat delta)
		{
		}

		ReturnValue GraphicsService::Render()
		{
			PostEffect::Begin();

			Render::SetOrthoMode();
			Render::EnableOrthoMode();
			Render::EnableAlphaBlend();

			GL_CHECK( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) );

			MPACK_DEV_PROFILE_BEGIN("Batcher");
			Batcher::FlushAll();
			MPACK_DEV_PROFILE_END();

			PostEffect::End();

			Debug::OpenGL::FlushErrors("GraphicsService::Render()");
			return RETURN_VALUE_OK;
		}

		ReturnValue GraphicsService::LoadResources()
		{
			Global::pFont=new TextureMappedFont;
			Global::pFont->Load("@Fonts/Font.tga",TextureMappedFont::RGB_MAGNITUDE);

			if(!LoadShaders())
			{
				LOGE("GraphicsService::LoadResources() failed to LoadShaders()");
				return RETURN_VALUE_KO;
			}

			return RETURN_VALUE_OK;
		}

		ReturnValue GraphicsService::UnloadResources()
		{
			if(Global::pFont)
			{
				delete Global::pFont;
			}

			DeleteShaders();

			return RETURN_VALUE_OK;
		}
	}
}
