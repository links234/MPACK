#ifndef MPACK_INIFILESECTION_HPP
#define MPACK_INIFILESECTION_HPP

#include "IniFileObject.hpp"

namespace MPACK
{
	namespace Core
	{
		class IniFile;
	}
}

namespace MPACK
{
	namespace Core
	{
		class IniFileSection
		{
		public:
			IniFileSection();
			~IniFileSection();

			IniFileObject* GetObject(std::string key) const;
			IniFileObject* AddObject(std::string key, std::string value);
			void DeleteObject(std::string key);

			bool IsValid() const;

		private:
			std::unordered_map<std::string,IniFileObject*> m_object;
			std::vector<IniFileObject*> m_objectOrder;

			static IniFileSection s_sentinel;

			friend class IniFile;
		};
	}
}

#endif
