#ifndef MPACK_CAMERA_HPP
#define MPACK_CAMERA_HPP

#include "Math.hpp"
#include "Frustum.hpp"
#include "Types.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Graphics
	{
		class Camera
		{
		public:
			Camera();
			virtual ~Camera();

			Matrix4f GetViewMatrix();
			Matrix4f GetProjMatrix();
			Matrix4f GetViewProjMatrix();

			GLfloat* GetViewMatrixPointer();
			GLfloat* GetProjMatrixPointer();
			GLfloat* GetViewProjMatrixPointer();

			virtual void Update(const GLfloat &delta);
			void SetClipPlane(const GLfloat &nearf, const GLfloat &farf);
			void SetViewport(const GLuint &width, const GLuint &height);
			void SetFOV(const GLfloat &fov);
			void SetVelocity(const Vector3f &velocity);
			void SetMinFOV(const GLfloat &angle);
			void SetMaxFOV(const GLfloat &angle);
			void LookAt(const Vector3f &point, Vector3f up=Vector3f(0.0f,1.0f,0.0f));
			void SetPosition(const Vector3f &position);

			Vector3f GetLookVector3();
			Vector3f GetUpVector3();
			Vector3f GetRightVector3();
			Vector3f GetPositionVector3();
			Vector3f GetVelocityVector3();

			GLfloat GetFOV();
			GLfloat GetMinFOV();
			GLfloat GetMaxFOV();
			GLfloat GetNear();
			GLfloat GetFar();

			GLuint GetHeight();
			GLuint GetWidth();

			Frustum* GetFrustumPointer();

		protected:
			void Adjust(const Matrix4f &matrix);
			void RegenerateVectors();
			void GetOrientationFromMatrix();

			bool	 m_updateProjection;
			GLuint	 m_width,m_height;
			GLfloat	 m_fovMin;
			GLfloat	 m_fovMax;
			GLfloat	 m_fov;
			GLfloat	 m_near,m_far;
			Vector3f m_look;
			Vector3f m_right;
			Vector3f m_up;
			Vector3f m_position;
			Vector3f m_velocity;
			Matrix4f m_viewMatrix;
			Matrix4f m_projectionMatrix;
			Matrix4f m_viewProjMatrix;
			Frustum  m_frustum;
		};

		class FreeCamera : public Camera
		{
		public:
			FreeCamera();

			virtual void Update(const GLfloat &delta);

			float GetFriction();
			float GetMinFriction();

			void SetFriction(const GLfloat &friction);
			void SetMinFriction(const GLfloat &minFriction);

			void AddPitch(const GLfloat &angle);
			void AddRoll(const GLfloat &angle);
			void AddYaw(const GLfloat &angle);

		private:
			float m_friction;
			float m_minFriction;
		};
	}
}

#endif
