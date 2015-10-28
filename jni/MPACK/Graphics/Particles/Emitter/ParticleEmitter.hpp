#ifndef MPACK_PARTICLEEMITTER_HPP
#define MPACK_PARTICLEEMITTER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class ParticleEffector;
	}
}

namespace MPACK
{
	namespace Graphics
	{
		class ParticleEmitter
		{
		public:
			ParticleEmitter();
			virtual ~ParticleEmitter();

			virtual void Update(GLfloat delta);

			static void UpdateAll(GLfloat delta);
			static void ClearAll();

			std::vector<ParticleEffector*>	m_modifiers;
		private:
			static std::unordered_set<ParticleEmitter*> m_emitters;
		};
	}
}

#endif
