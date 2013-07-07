#ifndef PHYSICSOBJECT_HPP
#define PHYSICSOBJECT_HPP

#include "PhysicsService.hpp"
#include "PShape.hpp"

using namespace std;

namespace Core
{
	class PObject
	{
	public:
		PObject(PShape p_shape);

		void SetPosition(PVec2 p_position);
		void SetLinearVelocity(PVec2 p_linearVelocity);
		void SetAngle(float p_angle);
		void SetAngularVelocity(float p_angularVelocity);
		void SetUserData(void* p_userData);

		const PVec2& GetPosition() const;
		const PVec2& GetLinearVelocity() const;
		float GetAngle() const;
		float GetAngularVelocity() const;
		void* GetUserData() const;
		const PAABB& GetAABB() const;
		const PShape* GetShape() const;
	private:

		friend class PhysicsService;

		void Advance(float dt);

		PVec2 m_position, m_linearVelocity;
		float m_angle, m_angularVelocity;

		PShape* m_shape;
		PAABB m_aabb;
		void* m_userData;

		list<PObject*>::iterator m_iterator;
	};

	inline void PObject::SetPosition(const PVec2& p_position) { m_position = p_position; }
	inline void PObject::SetLinearVelocity(const PVec2& p_linearVelocity) { m_linearVelocity = p_linearVelocity; }
	inline void PObject::SetAngle(float p_angle) { m_angle = p_angle; }
	inline void PObject::SetAngularVelocity(float p_angularVelocity) { m_angularVelocity = p_angularVelocity; }
	inline void PObject::SetUserData(void* p_userData) { m_userData = p_userData; }

	inline const PVec2& PObject::GetPosition() const { return m_position; }
	inline const PVec2& PObject::GetLinearVelocity() const { return m_linearVelocity; }
	inline float PObject::GetAngle() const { return m_angle; }
	inline float PObject::GetAngularVelocity() const { return m_angularVelocity; }
	inline void* PObject::GetUserData() const { return m_userData; }
	inline PAABB& PObject::GetAABB() const { return m_aabb; }
	inline const PShape* PObject::GetShape() const { return m_shape; }
}

#endif
