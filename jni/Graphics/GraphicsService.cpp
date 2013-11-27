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

    	return RETURN_VALUE_OK;
    }

    void GraphicsService::Stop()
    {
    	LOGI("GraphicsService::Stop");

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
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SpriteBatcher::FlushAll();
		return RETURN_VALUE_OK;
    }

    ReturnValue GraphicsService::LoadResources()
    {
		Global::pFont=new TextureMappedFont;
		Global::pFont->Load("@Fonts/Font.tga");

    	InitVertexPrograms();

    	return RETURN_VALUE_OK;
    }

    ReturnValue GraphicsService::UnloadResources()
    {
    	delete Global::pFont;

    	DeleteVertexPrograms();

    	return RETURN_VALUE_OK;
    }
}
