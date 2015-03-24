#ifndef MPACK_INDEXEDSKIPLISTLINK_HPP
#define MPACK_INDEXEDSKIPLISTLINK_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> class IndexedSkipList;
		template<class T> class IndexedSkipListNode;
	}
}

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> class IndexedSkipListLink
		{
		private:
			IndexedSkipListLink();

			int width;
			IndexedSkipListNode<T> *next;

			friend class IndexedSkipListNode<T>;
			friend class IndexedSkipList<T>;
		};
	}
}

#include "IndexedSkipListLinkImplementation.hpp"

#endif
