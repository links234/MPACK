#include "WaterObject.hpp"

#include "MPACK.hpp"
#include "Render.hpp"
#include "DemoApplication.hpp"
#include "Context.hpp"
#include <cassert>

using namespace MPACK;
using namespace MPACK::Math;
using namespace MPACK::Graphics;

const Vector2f WaterObject::s_targetHeight = Vector2f(0.f, 300.f);
const float	WaterObject::s_dampening = 0.1f;
const int WaterObject::m_springsCount = 201;
WaterObject* WaterObject::g_water = nullptr;

WaterObject::WaterObject()
	: m_spread(0.4f)
{

	CreateSprings();

	m_pWhiteTexture = new Texture2D;
	m_pWhiteTexture->Load("@Backgrounds/whitetexture.png");
	m_pWhiteTexture->SetWrapMode(GL_REPEAT, GL_REPEAT);

	/// create dem positions regarding to screen width
}

void WaterObject::CreateSprings()
{
	m_springs.reserve(m_springsCount);

	float step = 1.f * Render::GetScreenWidth() / (m_springsCount - 1);

	for (int i = 0; i < m_springsCount; ++ i)
	{
		WaterSpring currentSpring;
		currentSpring.m_position.x = i*step;
		m_springs.push_back(currentSpring);
	}
}

void WaterObject::CreateWavesVertices()
{
	for (int i = 1; i < m_springs.size(); ++ i)
	{
		SpriteVertex vertices[3];
		GLushort indices[3];

		for (int j = 0; j < 3; ++ j) indices[j] = j;

		const float x1 = m_springs[i-1].m_position.x;
		const float x2 = m_springs[i].m_position.x;
		const float y1 = m_springs[i-1].m_position.y;
		const float y2 = m_springs[i].m_position.y;

		//LOGI("%lf %lf %lf %lf", x1, y1, x2, y2);
		const float downCoord = Render::GetScreenHeight();

		//LOGI("%f", downCoord);


		vertices[0] = SpriteVertex(x1, downCoord, 0.f, 0.f, 0.f, 0.f, 0.f, 0.7f, SpriteVertex::ALPHA_BLEND);
		vertices[1] = SpriteVertex(x2, downCoord - y2, 1.f, 0.f, 0.f, 0.f, 1.f, 0.5f, SpriteVertex::ALPHA_BLEND);
		vertices[2] = SpriteVertex(x1, downCoord - y1, 0.f, 1.f, 0.f, 0.f, 1.f, 0.5f, SpriteVertex::ALPHA_BLEND);

		Batcher::SendSpriteVertexData(vertices, 3, indices, 3, m_pWhiteTexture, IndexData::TRIANGLES, 0.f);

		vertices[2] = SpriteVertex(x2, downCoord - y2, 1.f, 0.f, 0.f, 0.f, 1.f, 0.5f, SpriteVertex::ALPHA_BLEND);
		vertices[0] = SpriteVertex(x1, downCoord, 0.f, 0.f, 0.f, 0.f, 0.f, 0.7f, SpriteVertex::ALPHA_BLEND);
		vertices[1] = SpriteVertex(x2, downCoord, 0.f, 1.f, 0.f, 0.f, 0.f, 0.7f, SpriteVertex::ALPHA_BLEND);

		Batcher::SendSpriteVertexData(vertices, 3, indices, 3, m_pWhiteTexture, IndexData::TRIANGLES, 0.f);
	}

}

void WaterObject::Update(float dtime)
{
	for (auto &spring : m_springs)
		spring.Update(dtime);

	Vector2f leftDeltas[m_springs.size()];
	Vector2f rightDeltas[m_springs.size()];

	for (int i = 0; i < m_springs.size(); ++ i)
		leftDeltas[i] = rightDeltas[i] = Vector2f(0.f, 0.f);

	for (int j = 0; j < 8; j++)
	{
	    for (int i = 0; i < m_springs.size(); ++ i)
	    {
	        if (i > 0)
	        {
	            leftDeltas[i] = (m_springs[i].m_position - m_springs[i - 1].m_position) * m_spread;
	            m_springs[i - 1].m_velocity.y += leftDeltas[i].y; //
	        }
	        if (i < m_springs.size() - 1)
	        {
	            rightDeltas[i] = (m_springs[i].m_position - m_springs[i + 1].m_position) * m_spread;
	            m_springs[i + 1].m_velocity.y += rightDeltas[i].y;
	        }
	    }

	    for (int i = 0; i < m_springs.size(); ++ i)
	    {
	        if (i > 0)
	            m_springs[i - 1].m_position.y += leftDeltas[i].y;
	        if (i < m_springs.size() - 1)
	        	m_springs[i + 1].m_position.y += rightDeltas[i].y;
	    }
	}
}

void WaterObject::Render()
{
	CreateWavesVertices();
}

int WaterObject::GetSpringsCount()
{
	return m_springsCount;
}

void WaterObject::Splash(int index, Vector2f velocity)
{
	if (!(0 <= index && index < m_springs.size()))
		return ;
	m_springs[index].m_velocity = velocity;
}

void WaterObject::ClickSplash(Vector2f pos)
{
	int index;
	if (pos.x < 0.f) index = 0;
	else if (pos.x > Render::GetScreenWidth()) index = m_springsCount;
	else
	{
		index = pos.x * m_springsCount / Render::GetScreenWidth();
	}
	Splash(index, Vector2f(0.f, 500.f));
}

WaterObject::~WaterObject()
{

	delete m_pWhiteTexture;

}
