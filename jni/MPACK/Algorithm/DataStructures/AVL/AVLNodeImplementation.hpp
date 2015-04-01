#ifndef MPACK_AVLNODEIMPLEMENTATION_HPP
#define MPACK_AVLNODEIMPLMENETATION_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> AVLNode<T>::AVLNode(T value, int count)
			: m_value(value), m_count(count), m_height(0), m_weight(1),
			  m_balance(0), m_left(NULL), m_right(NULL)
		{
		}

		template<class T> void AVLNode<T>::UpdateHeight()
		{
			m_height = 0;
			if(m_left && m_right)
			{
				if(m_left->m_height > m_right->m_height)
				{
					m_height = m_left->m_height + 1;
				}
				else
				{
					m_height = m_right->m_height + 1;
				}
			}
			else if(m_left)
			{
				m_height = m_left->m_height + 1;
			}
			else if(m_right)
			{
				m_height = m_right->m_height + 1;
			}
		}

		template<class T> void AVLNode<T>::UpdateWeight()
		{
			m_weight = m_count;
			if(m_left)
			{
				m_weight += m_left->m_weight;
			}
			if(m_right)
			{
				m_weight += m_right->m_weight;
			}
		}

		template<class T> void AVLNode<T>::UpdateBalance()
		{
			m_balance=0;
			if(m_left && m_right)
			{
				m_balance = m_left->m_height - m_right->m_height;
			}
			else if(m_left)
			{
				m_balance = m_left->m_height + 1;
			}
			else if(m_right)
			{
				m_balance = -( m_right->m_height + 1);
			}
		}

		template<class T> void AVLNode<T>::Update()
		{
			UpdateHeight();
			UpdateWeight();
			UpdateBalance();
		}
	}
}

#endif
