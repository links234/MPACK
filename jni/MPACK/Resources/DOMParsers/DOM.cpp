#include "DOM.hpp"

using namespace std;
using namespace MPACK::Algorithm;

namespace MPACK
{
	namespace Core
	{
		DOM DOM::s_sentinel;

		DOM::DOM()
			: m_isArray(false), m_isTerminal(false)
		{
		}

		DOM::DOM(std::string value, bool isTerminal)
			: m_value(value), m_isTerminal(isTerminal), m_isArray(false)
		{
		}

		DOM::~DOM()
		{
			Clear();
		}

		void DOM::Clear()
		{
			DeleteChilds();
			DeleteProperties();
			DeleteArray();
		}

		void DOM::DeleteChilds()
		{
			for(SearchList<string,DOM*>::Iterator it=m_childs.Begin();it!=m_childs.End();++it)
			{
				if(it->value->IsValid())
				{
					delete it->value;
				}
			}
			m_childs.Clear();
		}

		void DOM::DeleteProperties()
		{
			for(SearchList<string,DOM*>::Iterator it=m_properties.Begin();it!=m_properties.End();++it)
			{
				if(it->value->IsValid())
				{
					delete it->value;
				}
			}
			m_properties.Clear();
		}

		void DOM::DeleteArray()
		{
			for(vector<DOM*>::iterator it=m_array.begin();it!=m_array.end();++it)
			{
				if((*it)->IsValid())
				{
					delete *it;
				}
			}
			m_array.clear();
		}

		SearchList<string,DOM*>& DOM::Childs()
		{
			return m_childs;
		}

		SearchList<string,DOM*>& DOM::Properties()
		{
			return m_properties;
		}

		void DOM::AddString(std::string key, std::string value)
		{
			SearchList<string,DOM*>::Iterator it=m_childs.Find(key);
			if(it != m_childs.End())
			{
				delete it->value;
				it->value = new DOM(value, true);
			}
			else
			{
				m_childs.PushBack(key, new DOM(value, true) );
			}
		}

		DOM* DOM::At(int index) const
		{
			if(index >= m_array.size())
			{
				return &DOM::s_sentinel;
			}
			return m_array[index];
		}

		DOM* DOM::Child(string child)
		{
			SearchList<string,DOM*>::Iterator it=m_childs.Find(child);
			if(it == m_childs.End())
			{
				return &DOM::s_sentinel;
			}
			return it->value;
		}

		DOM* DOM::Property(string property)
		{
			SearchList<string,DOM*>::Iterator it=m_properties.Find(property);
			if(it == m_properties.End())
			{
				return &DOM::s_sentinel;
			}
			return it->value;
		}

		bool DOM::IsArray() const
		{
			return m_isArray;
		}

		bool DOM::IsTerminal() const
		{
			return m_isTerminal;
		}

		bool DOM::IsValid() const
		{
			return this != &DOM::s_sentinel;
		}

		string DOM::GetValue() const
		{
			return m_value;
		}

		void DOM::SetValue(string value)
		{
			m_isTerminal = true;
			m_value = value;
		}

		DOM* DOM::GetSentinel()
		{
			return &s_sentinel;
		}
	}
}
