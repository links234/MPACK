#include "VoidPointer.hpp"

namespace MPACK
{
	namespace Core
	{
		VoidPointer::VoidPointer(void *pointer, int typeId)
			: pointer(pointer), typeId(typeId)
		{
		}
	}
}
