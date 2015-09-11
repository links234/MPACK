#ifndef MPACK_WORLD_HPP
#define MPACK_WORLD_HPP

#include "Types.hpp"

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

			void Step(float delta);

			Body* Add(Shape *shape, float x, float y);
			void Destroy(Body *body);

			void Clear();

		private:
			float m_stepDelta, m_accumulator;
			int m_iterations;
			std::vector<Body*> m_bodies;
			std::vector<Manifold> m_contacts;
		};
	}
}

#endif
