#include "Camera.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Graphics
	{
		Camera::Camera()
			: m_width(0), m_height(0), m_updateProjection(false), m_near(1.0f), m_far(100.0f), m_look(0.0f,0.0f,1.0f), m_up(0.0f,1.0f,0.0f),
			m_right(1.0f,0.0f,0.0f), m_position(0.0f,0.0f,0.0f), m_fov(45.0f), m_fovMin(10.0f), m_fovMax(180.0f)
		{
		}

		Camera::~Camera()
		{
		}

		Matrix4f Camera::GetViewMatrix()
		{
			return m_viewMatrix;
		}

		Matrix4f Camera::GetProjMatrix()
		{
			return m_projectionMatrix;
		}

		Matrix4f Camera::GetViewProjMatrix()
		{
			return m_viewProjMatrix;
		}

		void Camera::Update(const GLfloat &delta)
		{
			if(m_updateProjection)
			{
				m_updateProjection=false;
				Matrix4<float>::SetPerspective(m_projectionMatrix,m_fov,(float)(m_width)/(float)(m_height),m_near,m_far);
			}
			RegenerateVectors();
			Matrix4<float>::SetCamera(m_viewMatrix,m_look,m_up,m_right,m_position);
			m_viewProjMatrix=m_viewMatrix*m_projectionMatrix;
			m_frustum.Update(&m_viewProjMatrix);
		}

		void Camera::SetClipPlane(const GLfloat &nearf, const GLfloat &farf)
		{
			m_near=nearf;
			m_far=farf;
			m_updateProjection=true;
		}

		void Camera::SetViewport(const GLuint &width, const GLuint &height)
		{
			m_width=width;
			m_height=height;
			m_updateProjection=true;
			glViewport(0,0,m_width,m_height);
		}

		void Camera::SetFOV(const GLfloat &fov)
		{
			if(fov>=m_fovMin && fov<=m_fovMax)
			{
				m_fov=fov;
				m_updateProjection=true;
			}
		}

		void Camera::SetVelocity(const Vector3f &velocity)
		{
			m_velocity=velocity;
		}

		void Camera::Adjust(const Matrix4f &matrix)
		{
			m_look=m_look*matrix;
			m_up=m_up*matrix;
			m_right=m_right*matrix;
		}

		void Camera::SetMinFOV(const GLfloat &angle)
		{
			m_fovMin=angle;
		}
		void Camera::SetMaxFOV(const GLfloat &angle)
		{
			m_fovMax=angle;
		}

		void Camera::RegenerateVectors()
		{
			m_look.Normalize();
			m_up=m_look.Cross(m_right);
			m_up.Normalize();
			Vector3f vu(m_up);
			vu=Vector3f()-vu;
			m_right=m_look.Cross(vu);
			m_right.Normalize();
		}

		Vector3f Camera::GetLookVector3()
		{
			Vector3f look(-m_look.x,-m_look.y,-m_look.z);
			return look;
		}

		Vector3f Camera::GetUpVector3()
		{
			return m_up;
		}

		Vector3f Camera::GetRightVector3()
		{
			return m_right;
		}

		Vector3f Camera::GetPositionVector3()
		{
			return m_position;
		}

		Vector3f Camera::GetVelocityVector3()
		{
			return m_velocity;
		}

		GLfloat Camera::GetFOV()
		{
			return m_fov;
		}

		GLfloat Camera::GetMinFOV()
		{
			return m_fovMin;
		}

		GLfloat Camera::GetMaxFOV()
		{
			return m_fovMax;
		}

		GLfloat Camera::GetNear()
		{
			return m_near;
		}

		GLfloat Camera::GetFar()
		{
			return m_far;
		}

		GLuint Camera::GetHeight()
		{
			return m_height;
		}

		GLuint Camera::GetWidth()
		{
			return m_width;
		}

		void Camera::GetOrientationFromMatrix()
		{
			m_right.x=m_viewMatrix.m_matrix[0][0];
			m_right.y=m_viewMatrix.m_matrix[1][0];
			m_right.z=m_viewMatrix.m_matrix[2][0];

			m_up.x=m_viewMatrix.m_matrix[0][1];
			m_up.y=m_viewMatrix.m_matrix[1][1];
			m_up.z=m_viewMatrix.m_matrix[2][1];

			m_look.x=m_viewMatrix.m_matrix[0][2];
			m_look.y=m_viewMatrix.m_matrix[1][2];
			m_look.z=m_viewMatrix.m_matrix[2][2];
		}

		void Camera::LookAt(const Vector3f &point, Vector3f up)
		{
			m_look=m_position-point;
			if(up.Magnitude()!=0.0f)
			{
				m_up=up;
			}
			m_right=m_up.Cross(m_look);
		}

		void Camera::SetPosition(const Vector3f &position)
		{
			m_position=position;
		}

		GLfloat* Camera::GetViewMatrixPointer()
		{
			return (GLfloat*)(&m_viewMatrix);
		}

		GLfloat* Camera::GetProjMatrixPointer()
		{
			return (GLfloat*)(&m_projectionMatrix);
		}

		GLfloat* Camera::GetViewProjMatrixPointer()
		{
			return (GLfloat*)(&m_viewProjMatrix);
		}

		Frustum* Camera::GetFrustumPointer()
		{
			return &m_frustum;
		}




		FreeCamera::FreeCamera()
			: Camera(), m_friction(0.0f), m_minFriction(0.0f)
		{
		}

		void FreeCamera::Update(const GLfloat &delta)
		{
			Vector3f velocityDir=m_velocity.Normalized();
			float velocity=m_velocity.Magnitude();
			float friction=Math::Misc<float>::Max(velocity*m_friction,m_minFriction);
			friction*=delta;
			m_velocity-=velocityDir*friction;
			if(m_velocity.Magnitude()<0.05f)
			{
				m_velocity=Vector3f();
			}
			m_position+=m_velocity*delta;
			Camera::Update(delta);
		}

		float FreeCamera::GetFriction()
		{
			return m_friction;
		}

		float FreeCamera::GetMinFriction()
		{
			return m_minFriction;
		}

		void FreeCamera::SetFriction(const GLfloat &friction)
		{
			m_friction=friction;
		}

		void FreeCamera::SetMinFriction(const GLfloat &minFriction)
		{
			m_minFriction=minFriction;
		}

		void FreeCamera::AddPitch(const GLfloat &angle)
		{
			Matrix4f rotation;
			Matrix4<float>::SetAxisRotation(rotation,m_right,angle);
			Adjust(rotation);
		}

		void FreeCamera::AddRoll(const GLfloat &angle)
		{
			Matrix4f rotation;
			Matrix4<float>::SetAxisRotation(rotation,m_look,angle);
			Adjust(rotation);
		}

		void FreeCamera::AddYaw(const GLfloat &angle)
		{
			Matrix4f rotation;
			Matrix4<float>::SetAxisRotation(rotation,m_up,angle);
			Adjust(rotation);
		}
	}
}
