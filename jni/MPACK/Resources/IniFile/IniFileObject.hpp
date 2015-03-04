#ifndef MPACK_INIFILEOBJECT_HPP
#define MPACK_INIFILEOBJECT_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class IniFile;
		class IniFileSection;
	}
}

namespace MPACK
{
	namespace Core
	{
		class IniFileObject
		{
		public:
			IniFileObject();
			~IniFileObject();

			std::string GetValue() const;
			void SetValue(std::string value);

			bool IsValid() const;

		private:
			std::string m_value;

			static IniFileObject s_sentinel;

			friend class IniFile;
			friend class IniFileSection;
		};
	}
}

#endif
