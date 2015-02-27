#ifndef MPACK_INDEXEDSKIPLIST_HPP
#define MPACK_INDEXEDSKIPLIST_HPP

#include "IndexedSkipListNode.hpp"

namespace MPACK
{
	namespace Algorithm
	{
		const int IndexedSkipList_DefaultMaxHeight=18;

		template<class T> class IndexedSkipList
		{
		public:
			IndexedSkipList(int maxHeight=IndexedSkipList_DefaultMaxHeight);
			~IndexedSkipList();

			int Size() const;
			bool Empty() const;

			void Insert(int pos, T value);
			void Erase(int pos);

			T At(int pos) const;

		private:
			IndexedSkipListNode<T> *head;
			int m_size,m_maxHeight;
		};
	}
}

#include "IndexedSkipListImplementation.hpp"

#endif
