#ifndef MPACK_SEARCHLIST_HPP
#define MPACK_SEARCHLIST_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Algorithm
	{
		template<class TKey, class TValue> class SearchList
		{
		public:
			class Pair
			{
			public:
				Pair();
				Pair(TKey key);
				Pair(TKey key, TValue value);

				TKey key;
				TValue value;
			};

			class Iterator
			{
			public:
				Iterator();
				Iterator(const Iterator& other);

				const Iterator& operator= (const Iterator& other);

				Pair operator* () const;
				Pair* operator-> () const;

				Iterator& operator++ ();
				Iterator operator++ (int);
				Iterator& operator-- ();
				Iterator operator-- (int);

				bool operator!= (const Iterator &other) const;
				bool operator== (const Iterator &other) const;

			private:
				typename std::list<Pair>::iterator m_it;

				friend class SearchList<TKey,TValue>;
			};

			SearchList();
			~SearchList();

			void PushBack(TKey key, TValue value);
			void PopBack();

			void PushFront(TKey key, TValue value);
			void PopFront();

			Iterator Begin();
			Iterator End();
			Iterator Find(TKey key);

			void Erase(const TKey &key);
			void Erase(const Iterator &it);
			void Insert(const Iterator &it, TKey key, TValue value);

			TValue& operator[] (const TKey &key);

			void Clear();

			int Size();
			bool Empty();

		private:
			std::unordered_map<TKey,typename std::list<Pair>::iterator> m_hash;
			std::list<Pair> m_order;
		};
	}
}

#include "SearchListPairImplementation.hpp"

#include "SearchListIteratorImplementation.hpp"

#include "SearchListImplementation.hpp"

#endif
