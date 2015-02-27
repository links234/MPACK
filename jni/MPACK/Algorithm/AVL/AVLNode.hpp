#ifndef MPACK_AVLNODE_HPP
#define MPACK_AVLNODE_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> class AVL;
	}
}

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> class AVLNode
		{
		public:
			AVLNode(T value, int count=1);

			T m_value;

		private:
			void UpdateHeight();
			void UpdateWeight();
			void UpdateBalance();
			void Update();

			int m_count, m_height, m_weight, m_balance;
			AVLNode *m_left, *m_right;

			friend class AVL<T>;
		};
	}
}

#include "AVLNodeImplementation.hpp"

#endif
