#ifndef MPACK_AVLITERATOR_IMPL_HPP
#define MPACK_AVLITERATOR_IMPL_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> AVL<T>::Iterator::Iterator()
			: m_avl(NULL), m_node(NULL), m_count(0)
		{
		}

		template<class T> AVL<T>::Iterator::Iterator(const Iterator& other)
			: m_avl(other.m_avl), m_node(other.m_node), m_count(other.m_count)
		{
		}

		template<class T> const typename AVL<T>::Iterator& AVL<T>::Iterator::operator= (const typename AVL<T>::Iterator& other)
		{
			m_avl = other.m_avl;
			m_node = other.m_node;
			m_count = other.m_count;
			return other;
		}

		template<class T> T AVL<T>::Iterator::operator* () const
		{
			return m_node->m_value;
		}

		template<class T> const T* AVL<T>::Iterator::operator-> () const
		{
			return &m_node->m_value;
		}

		template<class T> typename AVL<T>::Iterator& AVL<T>::Iterator::operator++ ()
		{
			Next();
			return *this;
		}

		template<class T> typename AVL<T>::Iterator AVL<T>::Iterator::operator++ (int)
		{
			Iterator tempIt=*this;
			Next();
			return tempIt;
		}

		template<class T> typename AVL<T>::Iterator& AVL<T>::Iterator::operator-- ()
		{
			Prev();
			return *this;
		}

		template<class T> typename AVL<T>::Iterator AVL<T>::Iterator::operator-- (int)
		{
			Iterator tempIt=*this;
			Prev();
			return tempIt;
		}

		template<class T> bool AVL<T>::Iterator::operator!= (const Iterator &other) const
		{
			return this->m_node!=other.m_node || this->m_count!=other.m_count;
		}

		template<class T> bool AVL<T>::Iterator::operator== (const Iterator &other) const
		{
			return this->m_node==other.m_node && this->m_count==other.m_count;
		}

		template<class T> AVL<T>::Iterator::Iterator(AVL<T> *avl, AVLNode<T> *node, int count)
			: m_avl(avl), m_node(node), m_count(count)
		{
		}

		template<class T> void AVL<T>::Iterator::Next()
		{
			++m_count;
			if(m_count > m_node->m_count)
			{
				m_avl->m_param1 = m_node->m_value;
				m_node = m_avl->Next(m_avl->m_root);
				if(m_node)
				{
					m_count = 1;
				}
				else
				{
					m_count = 0;
				}
			}
		}

		template<class T> void AVL<T>::Iterator::Prev()
		{
			--m_count;
			if(m_count <= 0)
			{
				m_avl->m_param1 = m_node->m_value;
				m_node = m_avl->Prev(m_avl->m_root);
				if(m_node)
				{
					m_count = m_node->m_count;
				}
				else
				{
					m_count=0;
				}
			}
		}
	}
}

#endif
