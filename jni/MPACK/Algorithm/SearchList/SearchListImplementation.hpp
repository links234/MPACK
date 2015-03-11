#ifndef MPACK_SEARCHLISTIMPLEMENTATION_HPP
#define MPACK_SEARCHLISTIMPLEMENTATION_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class TKey, class TValue> SearchList<TKey,TValue>::SearchList()
		{
		}

		template<class TKey, class TValue> SearchList<TKey,TValue>::~SearchList()
		{
		}

		template<class TKey, class TValue> void SearchList<TKey,TValue>::PushBack(TKey key, TValue value)
		{
			typename std::unordered_map<TKey,typename std::list<Pair>::iterator>::iterator hash_it=m_hash.find(key);
			if(hash_it!=m_hash.end())
			{
				m_order.erase(hash_it->second);
				m_hash.erase(hash_it);
			}
			m_order.push_back(Pair(key,value));
			typename std::list<Pair>::iterator it=m_order.end();
			--it;
			m_hash[key]=it;
		}

		template<class TKey, class TValue> void SearchList<TKey,TValue>::PopBack()
		{
			TKey key=m_order.back().key;
			m_order.pop_back();
			m_hash.erase(key);
		}

		template<class TKey, class TValue> void SearchList<TKey,TValue>::PushFront(TKey key, TValue value)
		{
			typename std::unordered_map<TKey,typename std::list<Pair>::iterator>::iterator hash_it=m_hash.find(key);
			if(hash_it!=m_hash.end())
			{
				m_order.erase(hash_it->second);
				m_hash.erase(hash_it);
			}
			m_order.push_front(Pair(key,value));
			m_hash[key]=m_order.begin();
		}

		template<class TKey, class TValue> void SearchList<TKey,TValue>::PopFront()
		{
			TKey key=m_order.front().key;
			m_order.pop_front();
			m_hash.erase(key);
		}

		template<class TKey, class TValue> typename SearchList<TKey,TValue>::Iterator SearchList<TKey,TValue>::Begin()
		{
			typename SearchList<TKey,TValue>::Iterator it;
			it.m_it=m_order.begin();
			return it;
		}

		template<class TKey, class TValue> typename SearchList<TKey,TValue>::Iterator SearchList<TKey,TValue>::End()
		{
			typename SearchList<TKey,TValue>::Iterator it;
			it.m_it=m_order.end();
			return it;
		}

		template<class TKey, class TValue> typename SearchList<TKey,TValue>::Iterator SearchList<TKey,TValue>::Find(TKey key)
		{
			typename SearchList<TKey,TValue>::Iterator it;
			typename std::unordered_map<TKey,typename std::list<Pair>::iterator>::iterator hash_it=m_hash.find(key);
			if(hash_it==m_hash.end())
			{
				it.m_it=m_order.end();
			}
			else
			{
				it.m_it=hash_it->second;
			}
			return it;
		}

		template<class TKey, class TValue> void SearchList<TKey,TValue>::Erase(const TKey &key)
		{
			typename std::unordered_map<TKey,typename std::list<Pair>::iterator>::iterator hash_it=m_hash.find(key);
			if(hash_it!=m_hash.end())
			{
				m_order.erase(hash_it->second);
				m_hash.erase(hash_it);
			}
		}

		template<class TKey, class TValue> void SearchList<TKey,TValue>::Erase(const typename SearchList<TKey,TValue>::Iterator &it)
		{
			if(it.m_it!=m_order.end())
			{
				m_hash.erase(it.m_it->key);
				m_order.erase(it.m_it);
			}
		}

		template<class TKey, class TValue> void SearchList<TKey,TValue>::Insert(const typename SearchList<TKey,TValue>::Iterator &it, TKey key, TValue value)
		{
			typename std::unordered_map<TKey,typename std::list<Pair>::iterator>::iterator hash_it=m_hash.find(key);
			if(hash_it!=m_hash.end())
			{
				m_order.erase(hash_it->second);
				m_hash.erase(hash_it);
			}
			m_hash[key]=m_order.insert(it.m_it,SearchList<TKey,TValue>::Pair(key,value));
		}

		template<class TKey, class TValue> TValue& SearchList<TKey,TValue>::operator[] (const TKey &key)
		{
			typename std::unordered_map<TKey,typename std::list<Pair>::iterator>::iterator hash_it=m_hash.find(key);
			if(hash_it!=m_hash.end())
			{
				return hash_it->second->value;
			}
			m_order.push_back(Pair(key));
			typename std::list<Pair>::iterator it=m_order.end();
			--it;
			m_hash[key]=it;
			return it->value;
		}

		template<class TKey, class TValue> void SearchList<TKey,TValue>::Clear()
		{
		    m_hash.clear();
		    m_order.clear();
		}

		template<class TKey, class TValue> int SearchList<TKey,TValue>::Size()
		{
		    return m_order.size();
		}

		template<class TKey, class TValue> bool SearchList<TKey,TValue>::Empty()
		{
		    return m_order.empty();
		}
	}
}

#endif
