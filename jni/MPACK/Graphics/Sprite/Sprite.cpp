#include "Sprite.hpp"

using namespace std;
using namespace MPACK::Math;
using namespace MPACK::UI;

namespace MPACK
{
	namespace Graphics
	{
		Sprite::Sprite()
			: m_position(0,0), m_angle(0), m_width(0), m_height(0), m_texture(NULL), m_spriteShadingType(SpriteVertex::ALPHA_TEST),
			  m_layer(0), m_useCamera(false)
		{
			m_color[0]=m_color[1]=m_color[2]=m_color[3]=Math::Vector4f(1.0f,1.0f,1.0f,1.0f);
		}

		Sprite::~Sprite()
		{
		}

		AABB2Df Sprite::GetUISpace() const
		{
			return AABB2Df(-m_width,m_width,-m_height,m_height);
		}

		Anchor Sprite::GetUIPositionAnchor() const
		{
			return Anchor::Get(Anchor::Center);
		}

		void Sprite::Render()
		{
			Math::Vector2f v[4];
			v[0].x=-m_width;v[0].y=-m_height;
			v[0].Rotate(m_angle);
			v[0]+=m_position;

			v[1].x=+m_width;v[1].y=-m_height;
			v[1].Rotate(m_angle);
			v[1]+=m_position;

			v[2].x=+m_width;v[2].y=+m_height;
			v[2].Rotate(m_angle);
			v[2]+=m_position;

			v[3].x=-m_width;v[3].y=+m_height;
			v[3].Rotate(m_angle);
			v[3]+=m_position;

			swap(v[0],v[3]);
			swap(v[1],v[2]);

#ifdef PROFILE
			Profiler::RegisterCall_SpriteRender(m_texture, m_position.x - m_width, m_position.y - m_height,
												m_width * 2.0, m_height * 2.0, 0.0, 1.0, 0.0, 1.0);
#endif

			SpriteVertex vertexData[]={	SpriteVertex(v[0].x,v[0].y,	0,0,	m_color[0].x,m_color[0].y,m_color[0].z,m_color[0].w,	m_spriteShadingType),
										SpriteVertex(v[1].x,v[1].y,	1,0,	m_color[1].x,m_color[1].y,m_color[1].z,m_color[1].w,	m_spriteShadingType),
										SpriteVertex(v[2].x,v[2].y,	1,1,	m_color[2].x,m_color[2].y,m_color[2].z,m_color[2].w,	m_spriteShadingType),
										SpriteVertex(v[3].x,v[3].y,	0,1,	m_color[3].x,m_color[3].y,m_color[3].z,m_color[3].w,	m_spriteShadingType) };

			Batcher::SendSpriteVertexQuad(vertexData,4,m_texture,IndexData::TRIANGLES,m_layer);
		}

		void Sprite::SetSize(const GLfloat &width, const GLfloat &height)
		{
			m_width=width*0.5f;
			m_height=height*0.5f;
		}

		void Sprite::SetWidth(const GLfloat &width)
		{
			m_width=width*0.5f;
		}

		void Sprite::SetHeight(const GLfloat &height)
		{
			m_height=height*0.5f;
		}

		void Sprite::SetTexture(Texture2D *texture)
		{
			m_texture=texture;
			m_width=(GLfloat)(m_texture->GetWidth())*0.5f;
			m_height=(GLfloat)(m_texture->GetHeight())*0.5f;
		}

		void Sprite::SetColor(const Math::Vector4f &color)
		{
			m_color[0]=m_color[1]=m_color[2]=m_color[3]=color;
		}

		GLfloat Sprite::GetWidth()
		{
			return m_width*2.0f;
		}

		GLfloat Sprite::GetHeight()
		{
			return m_height*2.0f;
		}

		void Sprite::SetAngle(const GLfloat &angle)
		{
			m_angle=angle;
		}

		GLfloat Sprite::GetAngle() const
		{
			return m_angle;
		}
	
		void Sprite::SetShading(const GLfloat &shading)
		{
			m_spriteShadingType=shading;
		}
	
		GLfloat Sprite::GetShading() const
		{
			return m_spriteShadingType;
		}

		void Sprite::SetLayer(const GLfloat &layer)
		{
			m_layer=layer;
		}

		GLfloat Sprite::GetLayer() const
		{
			return m_layer;
		}

		void Sprite::UIWidgetCallback_SetPosition(const Math::Vector2f &position)
		{
			m_position=position;
		}

		void Sprite::UIWidgetCallback_SetX(const double &x)
		{
			m_position.x=x;
		}

		void Sprite::UIWidgetCallback_SetY(const double &y)
		{
			m_position.y=y;
		}

		Vector2f Sprite::UIWidgetCallback_GetPosition()
		{
			return m_position;
		}
	}
}
