#ifndef PHYSICSOBJECT_HPP
#define PHYSICSOBJECT_HPP


#include "PMath.hpp"
#include "list"

#include "PShape.hpp"
#include "PPoly.hpp"

using namespace std;

namespace Core
{
	class PShape;
	class PPoly;

	class PObject
	{
	public:
		PObject(const PShape* pShape=NULL);

		void 	SetPosition(const PVec2& position);
		const 	PVec2& GetPosition() const;

		void 	SetLinearVelocity(const PVec2& linearVelocity);
		const 	PVec2& GetLinearVelocity() const;

		void 	SetLinearAcceleration(const PVec2& linearAcceleration);
		const 	PVec2& GetLinearAcceleration() const;

		void 	SetAngle(float angle);
		float 	GetAngle() const;

		void 	SetAngularVelocity(float angularVelocity);
		float 	GetAngularVelocity() const;

		void 	SetUserData(void* userData);
		void* 	GetUserData() const;

		void 	SetMaxLinearVelocity(float maxLinearVelocity);
		float 	GetMaxLinearVelocity() const;

		void	SetFrictionThreshold(float frictionThreshold);
		float	GetFrictionThreshold() const;

		void	SetFrictionDynamic(float frictionDynamic);
		float	GetFrictionDynamic() const;

		const PAABB& 	GetAABB() const;
		const PShape* 	GetShape() const;
	protected:

		friend class PhysicsService;

		void Advance(float delta);

		PVec2 m_position, m_linearVelocity, m_linearAcceleration;
		float m_angle, m_angularVelocity;

		float m_frictionThreshold,m_frictionDynamic;
		float m_maxLinearVelocity;

		PShape* m_shape;
		PAABB m_aabb;
		void* m_userData;

		list<PObject*>::iterator m_iterator;
	};

	inline void 	PObject::SetPosition(const PVec2& position) { m_position = position; }
	inline const 	PVec2& PObject::GetPosition() const { return m_position; }

	inline void 	PObject::SetLinearVelocity(const PVec2& linearVelocity) { m_linearVelocity = linearVelocity; }
	inline const 	PVec2& PObject::GetLinearVelocity() const { return m_linearVelocity; }

	inline void 	PObject::SetLinearAcceleration(const PVec2& linearAcceleration) { m_linearAcceleration = linearAcceleration; }
	inline const	PVec2& PObject::GetLinearAcceleration() const { return m_linearAcceleration; }

	inline void 	PObject::SetAngle(float angle) { m_angle = angle; }
	inline float 	PObject::GetAngle() const { return m_angle; }

	inline void 	PObject::SetAngularVelocity(float angularVelocity) { m_angularVelocity = angularVelocity; }
	inline float 	PObject::GetAngularVelocity() const { return m_angularVelocity; }

	inline void 	PObject::SetUserData(void* userData) { m_userData = userData; }
	inline void* 	PObject::GetUserData() const { return m_userData; }

	inline void 	PObject::SetMaxLinearVelocity(float maxLinearVelocity) { m_maxLinearVelocity = maxLinearVelocity; }
	inline float 	PObject::GetMaxLinearVelocity() const { return m_maxLinearVelocity; }

	inline void	PObject::SetFrictionThreshold(float frictionThreshold) { m_frictionThreshold = frictionThreshold; }
	inline float	PObject::GetFrictionThreshold() const { return m_frictionThreshold; }

	inline void	PObject::SetFrictionDynamic(float frictionDynamic) { m_frictionDynamic = frictionDynamic; }
	inline float	PObject::GetFrictionDynamic() const { return m_frictionDynamic; }


	inline const PAABB& PObject::GetAABB() const { return m_aabb; }
	inline const PShape* PObject::GetShape() const { return m_shape; }
}

#endif
