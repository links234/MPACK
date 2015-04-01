#ifndef MPACK_INDEXEDSKIPLISTNODEIMPLEMENTATION_HPP
#define MPACK_INDEXEDSKIPLISTNODEIMPLEMENTATION_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> IndexedSkipListNode<T>::IndexedSkipListNode(T data, int height)
			: m_data(data), m_height(height)
		{
			link = new IndexedSkipListLink<T>[m_height];
		}

		template<class T> IndexedSkipListNode<T>::~IndexedSkipListNode()
		{
			delete[] link;
		}
	}
}

#endif
