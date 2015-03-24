#ifndef MPACK_INDEXEDSKIPLISTNODE_HPP
#define MPACK_INDEXEDSKIPLISTNODE_HPP

#include "IndexedSkipListLink.hpp"

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> class IndexedSkipList;
	}
}

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> class IndexedSkipListNode
		{
		private:
			IndexedSkipListNode(T data, int height);
			~IndexedSkipListNode();

			T m_data;
			int m_height;
			IndexedSkipListLink<T> *link;

			friend class IndexedSkipList<T>;
		};
	}
}

#include "IndexedSkipListNodeImplementation.hpp"

#endif
