#ifndef MPACK_RTTI_HPP
#define MPACK_RTTI_HPP

#include "VoidPointer.hpp"

namespace MPACK
{
	namespace Core
	{
		extern int MPACK_RTTITypeCounter;

		template<class T> int TypeId()
		{
			static int id=0;
			if(id==0)
			{
				++MPACK_RTTITypeCounter;
				id=MPACK_RTTITypeCounter;
			}
			return id;
		}

		template<class T> int TypeId(T object)
		{
			return TypeId<T>();
		}

		template<class T> VoidPointer ToVoidPointer(T pointer)
		{
			return VoidPointer(static_cast<void*>(pointer),TypeId<T>());
		}
	}
}

#endif
