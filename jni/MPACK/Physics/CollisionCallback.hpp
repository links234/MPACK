#ifndef MPACK_COLLISIONCALLBACK_HPP
#define MPACK_COLLISIONCALLBACK_HPP

namespace MPACK
{
	namespace Physics
	{
		class Body;
		class CollisionInfo;
	}
}

namespace MPACK
{
	namespace Physics
	{
		typedef void (*CollisionCallbackFunc)(void*,Body*,Body*,CollisionInfo*);

		struct CollisionCallbackStruct
		{
			CollisionCallbackStruct(CollisionCallbackFunc function, void *param1)
				:	function(function), param1(param1)
			{
			}

			CollisionCallbackFunc function;
			void *param1;

			bool operator== (const CollisionCallbackStruct &other)
			{
				if(function!=other.function)
					return false;
				if(param1!=other.param1)
					return false;
				return true;
			}
		};
	}
}

#endif
