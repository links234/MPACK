#ifndef MPACK_STATICSTACK_HPP
#define MPACK_STATICSTACK_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T, unsigned int StackSize> class StaticStack
		{
		public:
			StaticStack();

			void Push(const T &value);
			void Pop();
			T Top() const;

			void Clear();

			bool Empty() const;
			int Size() const;

		private:
			T m_data[StackSize];
			int m_index;
		};
	}
}

#include "StaticStackImplementation.hpp"

#endif
