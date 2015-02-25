#ifndef MPACK_CAMERA2D_HPP
#define MPACK_CAMERA2D_HPP

#include "MPACK.hpp"

#include <vector>

namespace MPACK
{
	namespace Graphics
	{
		class CameraObject;
	}
}

namespace MPACK
{
	namespace Graphics
	{
		class Camera2D
		{
		public:
			Camera2D();
			~Camera2D();

			void Update(GLfloat delta);

			void Transform(Math::Vector2f &vertex) const;
			void Link(CameraObject *target=NULL);

			void SetIdealPosition(const Math::Vector2f &idealPosition);
			Math::Vector2f GetIdealPosition() const;

			void SetPosition(const Math::Vector2f &position);
			Math::Vector2f GetPosition() const;

			void EnableSpringSystem();
			void DisableSpringSystem();

			void SetSpringConstant(const GLfloat &springConstant);

			void 	SetScale(const GLfloat &scale);
			GLfloat GetScale() const;

			void 		RotateDirection(const GLfloat &angle);
			void 		SetDirection(const Math::Vector2f &direction);
			Math::Vector2f 	GetDirection() const;

			static void UpdateAll(GLfloat delta);

		private:
			Math::Vector2f	m_position,m_velocity;
			Math::Vector2f 	m_idealPosition;
			CameraObject	*m_target;

			GLfloat			m_springConstant,m_dampingConstant;
			bool			m_useSpringSystem;

			GLfloat 		m_scale;

			Math::Vector2f	m_direction;

			static std::vector<Camera2D*> s_cameras;
		};
	}
}

#endif
