#include "IniFileSection.hpp"

using namespace std;
using namespace MPACK::Algorithm;

namespace MPACK
{
	namespace Core
	{
		IniFileSection IniFileSection::s_sentinel;

		IniFileSection::IniFileSection()
		{
		}

		IniFileSection::~IniFileSection()
		{
			for(SearchList<string,IniFileObject*>::Iterator it=m_object.Begin();it!=m_object.End();++it)
			{
				delete it->value;
			}
		}

		void IniFileSection::Clear()
		{
			for(SearchList<string,IniFileObject*>::Iterator it=m_object.Begin();it!=m_object.End();++it)
			{
				delete it->value;
			}
			m_object.Clear();
		}

		IniFileObject* IniFileSection::GetObject(string key)
		{
			SearchList<string,IniFileObject*>::Iterator it=m_object.Find(key);
			if(it==m_object.End())
			{
				return &IniFileObject::s_sentinel;
			}
			return it->value;
		}

		IniFileObject* IniFileSection::AddObject(string key, string value)
		{
			if(this==&s_sentinel)
			{
				return &IniFileObject::s_sentinel;
			}
			SearchList<string,IniFileObject*>::Iterator it=m_object.Find(key);
			if(it==m_object.End())
			{
				IniFileObject *pObj = new IniFileObject;
				pObj->m_value=value;
				m_object.PushBack(key,pObj);
				return pObj;
			}
			it->value->m_value=value;
			return it->value;
		}

		void IniFileSection::DeleteObject(string key)
		{
			if(this==&s_sentinel)
			{
				return;
			}
			m_object.Erase(key);
		}

		bool IniFileSection::IsValid() const
		{
			return this!=&s_sentinel;
		}
	}
}
