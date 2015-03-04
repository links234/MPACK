#include "IniFileObject.hpp"

using namespace std;

namespace MPACK
{
	namespace Core
	{
		IniFileObject IniFileObject::s_sentinel;

		IniFileObject::IniFileObject()
			: m_value("")
		{
		}

		IniFileObject::~IniFileObject()
		{
		}

		string IniFileObject::GetValue() const
		{
			return m_value;
		}

		void IniFileObject::SetValue(string value)
		{
			m_value=value;
		}

		bool IniFileObject::IsValid() const
		{
			return this!=&s_sentinel;
		}
	}
}
