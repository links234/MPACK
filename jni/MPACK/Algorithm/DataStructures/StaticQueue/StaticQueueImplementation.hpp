#ifndef MPACK_STATICQUEUEIMPLEMENTATION_HPP
#define MPACK_STATICQUEUEIMPLEMENTATION_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T, unsigned int QueueSize> StaticQueue<T,QueueSize>::StaticQueue()
			: m_begin(0), m_end(-1), m_state(e_empty)
		{
		}

		template<class T, unsigned int QueueSize> void StaticQueue<T,QueueSize>::Push(const T &value)
		{
			if(m_state==e_empty)
			{
				m_state=e_normal;
				m_data[++m_end]=value;
			}
			else
			{
				++m_end;
				if(m_end==QueueSize)
				{
					m_state=e_reverse;
					m_end=0;
				}
				m_data[m_end]=value;
			}
		}

		template<class T, unsigned int QueueSize> void StaticQueue<T,QueueSize>::Pop()
		{
			if(m_state==e_empty)
			{
				return;
			}
			++m_begin;
			if(m_begin==QueueSize)
			{
				if(m_end==QueueSize-1)
				{
					m_begin=m_end=0;
					m_state=e_empty;
					return;
				}
				m_state=e_normal;
				m_begin=0;
			}
			if(m_state==e_normal && m_begin>m_end)
			{
				m_state=e_empty;
				m_begin=0;
				m_end=-1;
			}
		}

		template<class T, unsigned int QueueSize> T StaticQueue<T,QueueSize>::Front() const
		{
			return m_data[m_begin];
		}

		template<class T, unsigned int QueueSize> void StaticQueue<T,QueueSize>::Clear()
		{
			m_begin=0;
			m_end=-1;
			m_state=e_empty;
		}

		template<class T, unsigned int QueueSize> bool StaticQueue<T,QueueSize>::Empty() const
		{
			return m_state==e_empty;
		}

		template<class T, unsigned int QueueSize> int StaticQueue<T,QueueSize>::Size() const
		{
			if(m_state==e_empty)
			{
				return 0;
			}
			if(m_state==e_normal)
			{
				return m_end-m_begin+1;
			}
			return m_end+QueueSize-m_begin+1;
		}
	}
}

#endif
