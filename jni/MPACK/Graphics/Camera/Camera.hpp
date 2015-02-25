#ifndef MPACK_CAMERA_HPP
#define MPACK_CAMERA_HPP

#include "Math.hpp"
#include "Frustum.hpp"
#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Camera
		{
		public:
			Camera();
			virtual ~Camera();

			Math::Matrix4f GetViewMatrix();
			Math::Matrix4f GetProjMatrix();
			Math::Matrix4f GetViewProjMatrix();

			GLfloat* GetViewMatrixPointer();
			GLfloat* GetProjMatrixPointer();
			GLfloat* GetViewProjMatrixPointer();

			virtual void Update(const GLfloat &delta);
			void SetClipPlane(const GLfloat &nearf, const GLfloat &farf);
			void SetViewport(const GLuint &width, const GLuint &height);
			void SetFOV(const GLfloat &fov);
			void SetVelocity(const Math::Vector3f &velocity);
			void SetMinFOV(const GLfloat &angle);
			void SetMaxFOV(const GLfloat &angle);
			void LookAt(const Math::Vector3f &point, Math::Vector3f up=Math::Vector3f(0.0f,1.0f,0.0f));
			void SetPosition(const Math::Vector3f &position);

			Math::Vector3f GetLookVector3();
			Math::Vector3f GetUpVector3();
			Math::Vector3f GetRightVector3();
			Math::Vector3f GetPositionVector3();
			Math::Vector3f GetVelocityVector3();

			GLfloat GetFOV();
			GLfloat GetMinFOV();
			GLfloat GetMaxFOV();
			GLfloat GetNear();
			GLfloat GetFar();

			GLuint GetHeight();
			GLuint GetWidth();

			Math::Frustum* GetFrustumPointer();

		protected:
			void Adjust(const Math::Matrix4f &matrix);
			void RegenerateVectors();
			void GetOrientationFromMatrix();

			bool	 m_updateProjection;
			GLuint	 m_width,m_height;
			GLfloat	 m_fovMin;
			GLfloat	 m_fovMax;
			GLfloat	 m_fov;
			GLfloat	 m_near,m_far;
			Math::Vector3f m_look;
			Math::Vector3f m_right;
			Math::Vector3f m_up;
			Math::Vector3f m_position;
			Math::Vector3f m_velocity;
			Math::Matrix4f m_viewMatrix;
			Math::Matrix4f m_projectionMatrix;
			Math::Matrix4f m_viewProjMatrix;
			Math::Frustum  m_frustum;
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
