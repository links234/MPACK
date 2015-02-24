#ifndef MPACK_CAMERA2D_HPP
#define MPACK_CAMERA2D_HPP

#include "MPACK.hpp"

using namespace std;
using namespace MPACK::Math;

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

			void Transform(Vector2f &vertex) const;
			void Link(CameraObject *target=NULL);

			void SetIdealPosition(const Vector2f &idealPosition);
			Vector2f GetIdealPosition() const;

			void SetPosition(const Vector2f &position);
			Vector2f GetPosition() const;

			void EnableSpringSystem();
			void DisableSpringSystem();

			void SetSpringConstant(const GLfloat &springConstant);

			void 	SetScale(const GLfloat &scale);
			GLfloat GetScale() const;

			void 		RotateDirection(const GLfloat &angle);
			void 		SetDirection(const Vector2f &direction);
			Vector2f 	GetDirection() const;

			static void UpdateAll(GLfloat delta);

		private:
			Vector2f		m_position,m_velocity;
			Vector2f 		m_idealPosition;
			CameraObject	*m_target;

			GLfloat			m_springConstant,m_dampingConstant;
			bool			m_useSpringSystem;

			GLfloat 		m_scale;

			Vector2f		m_direction;

			static vector<Camera2D*> s_cameras;
		};
	}
}

#endif
