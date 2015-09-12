#include "WaterState.hpp"

#include "Render.hpp"
#include "InputService.hpp"
#include "TimeService.hpp"
#include "DemoApplication.hpp"
#include "TextureMappedFont.hpp"
#include "Global.hpp"
#include "Context.hpp"
#include "Particles.hpp"
#include "Camera2D.hpp"
#include "WaterObject.hpp"

using namespace MPACK;
using namespace MPACK::Math;
using namespace MPACK::Core;
using namespace MPACK::Global;
using namespace MPACK::Graphics;
using namespace MPACK::UI;

namespace Game
{
	WaterState::WaterState()
	{
		m_pWSInputController = WSInputController::Initialize();
		Global::pActiveCamera = new Camera2D();

		m_pBackgroundTexture = new Texture2D();
		m_pBackgroundTexture->Load("@Backgrounds/skybk1.png");
		m_pBackgroundTexture->SetWrapMode(GL_REPEAT, GL_REPEAT);

		m_pWhiteTexture = new Texture2D();
		m_pWhiteTexture->Load("@Backgrounds/whitetexture.png");
		m_pWhiteTexture->SetWrapMode(GL_REPEAT, GL_REPEAT);


		m_pBackgroundSprite = new Sprite();
		m_pBackgroundSprite->SetTexture(m_pBackgroundTexture);
		m_pBackgroundSprite->SetColor(Vector4f(1.f, 1.f, 1.f, 1.f));
		m_pBackgroundSprite->m_position = Vector2f(Render::GetScreenWidth() / 2.f, Render::GetScreenHeight() / 2.f);
		m_pBackgroundSprite->SetLayer(-100000.0f);
		m_pBackgroundSprite->SetShading(SpriteVertex::ALPHA_BLEND);
		m_pBackgroundSprite->SetSize(Render::GetScreenWidth(), Render::GetScreenHeight());
	}

	int WaterState::Update()
	{

		float dtime = Global::pContext->pTimeService->Elapsed();

		m_pWSInputController->Update(dtime);

		m_water.Update(dtime);

		Camera2D::UpdateAll(dtime);

		if (m_pWSInputController->GetLeftMouseButtonPressed())
		{
			Vector2f pos = m_pWSInputController->GetMousePosition();
			//m_water.Splash(Random::Int(0, m_water.GetSpringsCount()), Vector2f(0.f, Random::Double(-2000.f, 2000.f)));//
			m_water.ClickSplash(pos);
			LOGI("(%f, %f)", pos.x, pos.y);
		}
		if (m_pWSInputController->IsUserRequestingExit())
		{
			return EVENT_WATER_EXIT;
		}
		return EVENT_NOTHING;
	}

	void WaterState::Render()
	{
		m_pBackgroundSprite->Render();

		/*SpriteVertex* vertices = new SpriteVertex[3];
		vertices[0] = SpriteVertex(0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, SpriteVertex::NONE);
		vertices[1] = SpriteVertex(0.f, 300.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, SpriteVertex::NONE);
		vertices[2] = SpriteVertex(400.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, SpriteVertex::NONE);
		GLushort* indices = new GLushort[3];

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		Batcher::SendSpriteVertexData(vertices, 3, indices, 3, m_pWhiteTexture, IndexData::TRIANGLES, 0.f);*/

		m_water.Render();

		m_pWSInputController->Render();
	}

	void WaterState::Pause()
	{

	}

	void WaterState::Continue()
	{

	}

	WaterState::~WaterState()
	{
		delete Global::pActiveCamera;
		delete m_pBackgroundSprite;
		delete m_pBackgroundTexture;
		delete m_pWhiteTexture;
		delete m_pWSInputController;
	}
}
