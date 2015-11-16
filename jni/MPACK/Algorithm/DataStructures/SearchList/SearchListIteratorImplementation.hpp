#ifndef MPACK_SEARCHLISTITERATORIMPLEMENTATION_HPP
#define MPACK_SEARCHLISTITERATORIMPLEMENTATION_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class TKey, class TValue> SearchList<TKey,TValue>::Iterator::Iterator()
		{
		}

		template<class TKey, class TValue> SearchList<TKey,TValue>::Iterator::Iterator(const SearchList<TKey,TValue>::Iterator& other)
		{
			m_it=other.m_it;
		}

		template<class TKey, class TValue> const typename SearchList<TKey,TValue>::Iterator& SearchList<TKey,TValue>::Iterator::operator= (const SearchList<TKey,TValue>::Iterator& other)
		{
			m_it=other.m_it;
			return other;
		}

		template<class TKey, class TValue> typename SearchList<TKey,TValue>::Pair SearchList<TKey,TValue>::Iterator::operator* () const
		{
			return *m_it;
		}

		template<class TKey, class TValue> typename SearchList<TKey,TValue>::Pair* SearchList<TKey,TValue>::Iterator::operator-> () const
		{
			return &(*m_it);
		}

		template<class TKey, class TValue> typename SearchList<TKey,TValue>::Iterator& SearchList<TKey,TValue>::Iterator::operator++ ()
		{
			++m_it;
			return *this;
		}

		template<class TKey, class TValue> typename SearchList<TKey,TValue>::Iterator SearchList<TKey,TValue>::Iterator::operator++ (int)
		{
			typename SearchList<TKey,TValue>::Iterator tempIt=*this;
			++m_it;
			return tempIt;
		}

		template<class TKey, class TValue> typename SearchList<TKey,TValue>::Iterator& SearchList<TKey,TValue>::Iterator::operator-- ()
		{
			--m_it;
			return *this;
		}

		template<class TKey, class TValue> typename SearchList<TKey,TValue>::Iterator SearchList<TKey,TValue>::Iterator::operator-- (int)
		{
			typename SearchList<TKey,TValue>::Iterator tempIt=*this;
			--m_it;
			return tempIt;
		}

		template<class TKey, class TValue> bool SearchList<TKey,TValue>::Iterator::operator!= (const typename SearchList<TKey,TValue>::Iterator &other) const
		{
			return m_it!=other.m_it;
		}

		template<class TKey, class TValue> bool SearchList<TKey,TValue>::Iterator::operator== (const typename SearchList<TKey,TValue>::Iterator &other) const
		{
			return m_it==other.m_it;
		}
	}
}

#endif
