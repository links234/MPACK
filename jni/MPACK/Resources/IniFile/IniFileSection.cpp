#include "IniFileSection.hpp"

using namespace std;

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
			for(vector<IniFileObject*>::iterator it=m_objectOrder.begin();it!=m_objectOrder.end();++it)
			{
				delete *it;
			}
		}

		IniFileObject* IniFileSection::GetObject(string key) const
		{
			unordered_map<string,IniFileObject*>::const_iterator it=m_object.find(key);
			if(it==m_object.end())
			{
				return &IniFileObject::s_sentinel;
			}
			return it->second;
		}

		IniFileObject* IniFileSection::AddObject(string key, string value)
		{
			if(this==&s_sentinel)
			{
				return &IniFileObject::s_sentinel;
			}
			unordered_map<string,IniFileObject*>::iterator it=m_object.find(key);

			if(it==m_object.end())
			{
				IniFileObject *pObj = new IniFileObject;
				pObj->m_value=value;
				m_objectOrder.push_back(pObj);
				m_object[key]=pObj;
				return pObj;
			}
			it->second->m_value=value;
			return it->second;
		}

		void IniFileSection::DeleteObject(string key)
		{
			if(this==&s_sentinel)
			{
				return;
			}
			unordered_map<string,IniFileObject*>::iterator it=m_object.find(key);
			if(it==m_object.end())
			{
				return;
			}
			int index=0;
			for(vector<IniFileObject*>::iterator it2=m_objectOrder.begin();it2!=m_objectOrder.end();++it2)
			{
				if(*it2==it->second)
				{
					delete *it2;
					swap(m_objectOrder[index],m_objectOrder[m_objectOrder.size()-1]);
					m_objectOrder.pop_back();
					return;
				}
				++index;
			}
		}

		bool IniFileSection::IsValid() const
		{
			return this!=&s_sentinel;
		}
	}
}
