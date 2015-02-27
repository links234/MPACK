#ifndef MPACK_AVL_IMPL_HPP
#define MPACK_AVL_IMPL_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> AVL<T>::AVL()
			: m_root(NULL), m_sentinel(this,NULL,0), m_param2(0)
		{
		}

		template<class T> AVL<T>::~AVL()
		{
			if(m_root)
			{
				Delete(m_root);
			}
		}

		template<class T> int AVL<T>::Size() const
		{
			if(m_root)
			{
				return m_root->m_weight;
			}
			return 0;
		}

		template<class T> bool AVL<T>::Empty() const
		{
			if(m_root)
			{
				return m_root->m_weight == 0;
			}
			return true;
		}

		template<class T> void AVL<T>::Clear()
		{
			Delete(m_root);
			m_root = NULL;
		}

		template<class T> typename AVL<T>::Iterator AVL<T>::Begin()
		{
			return Iterator(this,Min(m_root),1);
		}

		template<class T> typename AVL<T>::Iterator AVL<T>::End()
		{
			AVLNode<T> *node = Max(m_root);
			return Iterator(this,node,node->m_count);
		}

		template<class T> typename AVL<T>::Iterator AVL<T>::Sentinel() const
		{
			return m_sentinel;
		}

		template<class T> typename AVL<T>::Iterator AVL<T>::Find(T value) const
		{
			m_param1=value;

			AVLNode<T> *node = Find(m_root);
			if(node)
			{
				return Iterator(this,node);
			}
			return m_sentinel;
		}

		template<class T> void AVL<T>::Insert(T value, int cnt)
		{
			if(!m_root)
			{
				m_root=new AVLNode<T>(value,cnt);
				return;
			}
			m_param1=value;
			m_param2=cnt;

			m_root=Insert(m_root);
		}

		template<class T> void AVL<T>::Erase(T value, int cnt)
		{
			if(m_root)
			{
				m_param1=value;
				m_param2=cnt;

				m_root=Erase(m_root);
			}
		}

		template<class T> typename AVL<T>::Iterator AVL<T>::NthElement(int pos) const
		{
			if((pos < 1) || (pos > m_root->m_weight))
			{
				return m_sentinel;
			}
			m_param2 = pos;
			AVLNode<T> *node = NthElement(m_root);
			return Iterator(this,node,m_param2);
		}

		template<class T> void AVL<T>::Delete(AVLNode<T> *node)
		{
			if(node->m_left)
			{
				Delete(node->m_left);
			}
			if(node->m_right)
			{
				Delete(node->m_right);
			}
			delete node;
		}

		template<class T> AVLNode<T>* AVL<T>::Min(AVLNode<T> *node) const
		{
			if(!node)
			{
				return NULL;
			}
			if(node->m_left)
			{
				return Min(node->m_left);
			}
			return node;
		}

		template<class T> AVLNode<T>* AVL<T>::Max(AVLNode<T> *node) const
		{
			if(!node)
			{
				return NULL;
			}
			if(node->m_right)
			{
				return Max(node->m_right);
			}
			return node;
		}

		template<class T> AVLNode<T>* AVL<T>::Next(AVLNode<T> *node) const
		{
			if(!node)
			{
				return NULL;
			}
			if(m_param1 < node->m_value)
			{
				AVLNode<T> *temp=Next(node->m_left);
				if(!temp)
				{
					return node;
				}
				return temp;
			}
			else
			{
				return Next(node->m_right);
			}
		}

		template<class T> AVLNode<T>* AVL<T>::Prev(AVLNode<T> *node) const
		{
			if(!node)
			{
				return NULL;
			}
			if(node->m_value < m_param1)
			{
				AVLNode<T> *temp=Prev(node->m_right);
				if(!temp)
				{
					return node;
				}
				return temp;
			}
			else
			{
				return Prev(node->m_left);
			}
		}

		template<class T> AVLNode<T>* AVL<T>::Find(AVLNode<T> *node) const
		{
			if(!node)
			{
				return NULL;
			}
			if(m_param1<node->m_value)
			{
				return Find(node->m_left);
			}
			else if(node->m_value < m_param1)
			{
				return Find(node->m_right);
			}
			return node;
		}

		template<class T> AVLNode<T>* AVL<T>::Insert(AVLNode<T> *node)
		{
			if(!node)
			{
				return new AVLNode<T>(m_param1,m_param2);
			}
			if(m_param1<node->m_value)
			{
				node->m_left = Insert(node->m_left);
			}
			else if(node->m_value < m_param1)
			{
				node->m_right = Insert(node->m_right);
			}
			else
			{
				node->m_count += m_param2;
			}

			node = Balance(node);
			return node;
		}

		template<class T> AVLNode<T>* AVL<T>::RotateLeft(AVLNode<T> *node)
		{
			AVLNode<T> *temp=node->m_right;
			node->m_right = temp->m_left;
			temp->m_left = node;

			node->Update();
			temp->Update();

			return temp;
		}

		template<class T> AVLNode<T>* AVL<T>::RotateRight(AVLNode<T> *node)
		{
			AVLNode<T> *temp=node->m_left;
			node->m_left = temp->m_right;
			temp->m_right = node;

			node->Update();
			temp->Update();

			return temp;
		}

		template<class T> AVLNode<T>* AVL<T>::Balance(AVLNode<T> *node)
		{
			node->Update();
			if(node->m_balance==2)
			{
				if(node->m_left->m_balance<0)
				{
					node->m_left = RotateLeft(node->m_left);
				}
				node = RotateRight(node);
			}
			else if(node->m_balance==-2)
			{
				if(node->m_right->m_balance>0)
				{
					node->m_right = RotateRight(node->m_right);
				}
				node = RotateLeft(node);
			}

			return node;
		}

		template<class T> AVLNode<T>* AVL<T>::Erase(AVLNode<T> *node)
		{
			if(!node)
			{
				return NULL;
			}
			if(m_param1 < node->m_value)
			{
				node->m_left = Erase(node->m_left);
			}
			else if(node->m_value < m_param1)
			{
				node->m_right = Erase(node->m_right);
			}
			else
			{
				node->m_count -= m_param2;

				if(node->m_count <= 0)
				{
					if(!node->m_left && !node->m_right)
					{
						delete node;
						return NULL;
					}
					else if(!node->left)
					{
						AVLNode<T> *temp = node->m_right;
						delete node;
						node = temp;
					}
					else if(!node->right)
					{
						AVLNode<T> *temp = node->m_left;
						delete node;
						node = temp;
					}
					else
					{
						AVLNode<T> *temp = Max(node->m_left);
						node->m_value = temp->m_value;
						node->m_count = temp->m_count;

						m_param1=temp->m_value;
						temp->m_count = 0;

						node->m_left = Erase(node->m_left);
					}
				}
			}

			node = Balance(node);
			return node;
		}

		template<class T> AVLNode<T>* AVL<T>::NthElement(AVLNode<T> *node) const
		{
			if(node->m_left)
			{
				if(node->m_left->m_weight >= m_param2)
				{
					return NthElement(node->m_left);
				}
				m_param2 -= node->m_left->m_weight;
			}
			if(node->m_count >= m_param2)
			{
				return node;
			}
			if(node->m_right)
			{
				m_param2 -= node->m_count;
				return NthElement(node->m_right);
			}
			return NULL;
		}
	}
}

#endif

