#ifndef MPACK_AVL_HPP
#define MPACK_AVL_HPP

#include "AVLNode.hpp"

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> class AVL
		{
		public:
			class Iterator
			{
			public:
				Iterator();
				Iterator(const Iterator& other);

				const Iterator& operator= (const Iterator& other);

				T operator* () const;
				const T* operator-> () const;

				Iterator& operator++ ();
				Iterator operator++ (int);
				Iterator& operator-- ();
				Iterator operator-- (int);

				bool operator!= (const Iterator &other) const;
				bool operator== (const Iterator &other) const;

			private:
				Iterator(AVL<T> *avl, AVLNode<T> *node, int count=1);

				void Next();
				void Prev();

				AVL<T> *m_avl;
				AVLNode<T> *m_node;
				int m_count;

				friend class AVL<T>;
			};

			AVL();
			~AVL();

			int Size() const;
			bool Empty() const;
			void Clear();

			Iterator Begin();
			Iterator End();
			Iterator Sentinel() const;

			Iterator Find(T value) const;

			void Insert(T value, int cnt=1);
			void Erase(T value, int cnt=1);

			Iterator NthElement(int pos) const;

		private:
			void Delete(AVLNode<T> *node);

			AVLNode<T>* Min(AVLNode<T> *node) const;
			AVLNode<T>* Max(AVLNode<T> *node) const;

			AVLNode<T>* Next(AVLNode<T> *node) const;
			AVLNode<T>* Prev(AVLNode<T> *node) const;

			AVLNode<T>* Find(AVLNode<T> *node) const;

			AVLNode<T>* Insert(AVLNode<T> *node);
			AVLNode<T>* Erase(AVLNode<T> *node);

			AVLNode<T>* RotateLeft(AVLNode<T> *node);
			AVLNode<T>* RotateRight(AVLNode<T> *node);
			AVLNode<T>* Balance(AVLNode<T> *node);

			AVLNode<T>* NthElement(AVLNode<T> *node) const;

			AVLNode<T> *m_root;
			Iterator m_sentinel;

			//internal use, no actual data stored here
			T m_param1;
			int m_param2;
		};
	}
}

#include "AVLIteratorImplementation.hpp"

#include "AVLImplementation.hpp"

#endif
