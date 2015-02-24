/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MPACK_SPRITE_HPP
#define MPACK_SPRITE_HPP

#include "Math.hpp"
#include "Types.hpp"
#include "SpriteBatcher.hpp"
#include "Texture2D.hpp"
#include "Render.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Sprite
		{
		public:
			Sprite();
			virtual ~Sprite();

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
