#ifndef MPACK_STATICSTACKIMPLEMENTATION_HPP
#define MPACK_STATICSTACKIMPLEMENTATION_HPP

namespace MPACK
{
	namespace Algorithm
	{
		template<class T, unsigned int StackSize> StaticStack<T,StackSize>::StaticStack()
			: m_index(-1)
		{
		}

		template<class T, unsigned int StackSize> void StaticStack<T,StackSize>::Push(const T &value)
		{
			m_data[++m_index]=value;
		}

		template<class T, unsigned int StackSize> void StaticStack<T,StackSize>::Pop()
		{
			if(m_index > -1)
			{
				--m_index;
			}
		}

		template<class T, unsigned int StackSize> T StaticStack<T,StackSize>::Top() const
		{
			return m_data[m_index];
		}

		template<class T, unsigned int StackSize> void StaticStack<T,StackSize>::Clear()
		{
			m_index = -1;
		}

		template<class T, unsigned int StackSize> bool StaticStack<T,StackSize>::Empty() const
		{
			return m_index <= -1;
		}

		template<class T, unsigned int StackSize> int StaticStack<T,StackSize>::Size() const
		{
			return m_index + 1;
		}
	}
}

#endif
