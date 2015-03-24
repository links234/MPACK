#ifndef MPACK_STATICQUEUE_HPP
#define MPACK_STATICQUEUE_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T, unsigned int QueueSize> class StaticQueue
		{
		public:
			StaticQueue();

			enum State{e_empty, e_normal, e_reverse};

			void Push(const T &value);
			void Pop();
			T Front() const;

			void Clear();

			bool Empty() const;
			int Size() const;

		private:
			T m_data[QueueSize];
			int m_begin,m_end;
			State m_state;
		};
	}
}
#include "StaticQueueImplementation.hpp"

#endif

