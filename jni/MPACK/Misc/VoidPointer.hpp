#ifndef MPACK_VOIDPOINTER_HPP
#define MPACK_VOIDPOINTER_HPP

namespace MPACK
{
	namespace Core
	{
		class VoidPointer
		{
		public:
			VoidPointer(void *pointer=0, int typeId=0);

			int typeId;
			void *pointer;
		};
	}
}

#endif
