#include "GraphicsService.hpp"

#include "Global.hpp"
#include "TimeService.hpp"
#include "Render.hpp"
#include "Texture2D.hpp"
#include "TextureMappedFont.hpp"
#include "Log.hpp"
#include "Particles.hpp"
#include "Object.hpp"
#include "Context.hpp"
#include "Camera2D.hpp"
#include "Sprite.hpp"
#include "AnimatedSprite.hpp"
#include "ShaderTypes.hpp"
#include "PostEffect.hpp"

namespace Core
{
    GraphicsService::GraphicsService()
    {
    	LOGI("Creating GraphicsService.");
    }

    ReturnValue GraphicsService::Start()
    {
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
    	LOGI("GraphicsService::Stop");

    	PostEffect::Shutdown();

    	UnloadResources();

    	Render::DisableAlphaBlend();
    	Render::DisableOrthoMode();
    	Render::Uninit();
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

    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SpriteBatcher::FlushAll();

		PostEffect::End();

		return RETURN_VALUE_OK;
    }

    ReturnValue GraphicsService::LoadResources()
    {
		Global::pFont=new TextureMappedFont;
		Global::pFont->Load("@Fonts/Font.tga");

    	LoadShaders();

    	return RETURN_VALUE_OK;
    }

    ReturnValue GraphicsService::UnloadResources()
    {
    	delete Global::pFont;

    	DeleteShaders();

    	return RETURN_VALUE_OK;
    }
}
