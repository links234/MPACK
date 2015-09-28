#ifndef MPACK_WORLD_HPP
#define MPACK_WORLD_HPP

#include "Types.hpp"

#include "CollisionCallback.hpp"

#include "Body.hpp"
#include "Shape.hpp"
#include "Manifold.hpp"

namespace MPACK
{
	namespace Physics
	{
		class World
		{
		public:
			World(float delta, int iterations);
			~World();

			void Update(float delta);

			Body* Add(Shape *shape, float x, float y);
			void Destroy(Body *body);

			void Clear();

			void LinkCollisionCallback(const CollisionCallbackStruct &link);
			void UnLinkCollisionCallback(const CollisionCallbackStruct &link);

			void DebugDraw();

			void EnableDebugDraw();
			void DisableDebugDraw();

		private:
			void Step(float delta);

			bool m_debugDraw;

			float m_stepDelta, m_accumulator;
			int m_iterations;
			std::unordered_set<Body*> m_bodies;
			std::vector<Manifold> m_contacts;

			std::vector<CollisionCallbackStruct> m_collisionCallbackFunc;
		};
	}
}

#endif
