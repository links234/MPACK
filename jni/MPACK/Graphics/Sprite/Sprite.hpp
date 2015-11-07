#ifndef MPACK_SPRITE_HPP
#define MPACK_SPRITE_HPP

#include "Math.hpp"
#include "Types.hpp"
#include "Batcher.hpp"
#include "Texture2D.hpp"
#include "Render.hpp"
#include "UI.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Sprite : public UI::UIWidget
		{
		public:
			Sprite();
			virtual ~Sprite();

			virtual Math::AABB2Df GetUISpace() const;
			virtual UI::Anchor GetUIPositionAnchor() const;

			virtual void Render();

			void SetSize(const GLfloat &width, const GLfloat &height);
			void SetWidth(const GLfloat &width);
			void SetHeight(const GLfloat &height);
			void SetTexture(Texture2D *texture);
			void SetColor(const Math::Vector4f &color);

			GLfloat GetWidth();
			GLfloat GetHeight();

			void SetAngle(const GLfloat &angle);
			GLfloat GetAngle() const;

			void SetShading(const GLfloat &shading);
			GLfloat GetShading() const;

			void SetLayer(const GLfloat &layer);
			GLfloat GetLayer() const;

			Math::Vector2f	m_position;
			Math::Vector4f	m_color[4];

		protected:
			virtual void UIWidgetCallback_SetPosition(const Math::Vector2f &position);
			virtual void UIWidgetCallback_SetX(const double &x);
			virtual void UIWidgetCallback_SetY(const double &y);
			virtual Math::Vector2f UIWidgetCallback_GetPosition();

			GLfloat			m_width,m_height;
			Texture2D		*m_texture;

			GLfloat			m_spriteShadingType;
			GLfloat			m_layer;
			GLfloat			m_angle;
			bool 			m_useCamera;
		};
	}
}

#endif
