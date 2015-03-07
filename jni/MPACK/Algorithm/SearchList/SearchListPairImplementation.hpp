#ifndef MPACK_SEARCHLISTPAIRIMPLEMENTATION_HPP
#define MPACK_SEARCHLISTPAIRIMPLEMENTATION_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class TKey, class TValue> SearchList<TKey,TValue>::Pair::Pair()
		{
		}

		template<class TKey, class TValue> SearchList<TKey,TValue>::Pair::Pair(TKey key)
			: key(key)
		{
		}

		template<class TKey, class TValue> SearchList<TKey,TValue>::Pair::Pair(TKey key, TValue value)
			: key(key), value(value)
		{
		}
	}
}
#endif
