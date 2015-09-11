#ifndef MPACK_MATERIAL_HPP
#define MPACK_MATERIAL_HPP

namespace MPACK
{
	namespace Physics
	{
		class Material
		{
		public:
			Material();

			float density;
			float restitution;
			float staticFriction;
			float dynamicFriction;
		};
	}
}

#endif
