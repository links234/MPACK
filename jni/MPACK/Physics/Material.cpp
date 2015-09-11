#include "Material.hpp"

namespace MPACK
{
	namespace Physics
	{
		Material::Material()
			: density(1.0f), restitution(0.3f), staticFriction(0.2f), dynamicFriction(0.4)
		{
		}
	}
}
