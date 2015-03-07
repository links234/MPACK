#ifndef MPACK_INIFILESECTION_HPP
#define MPACK_INIFILESECTION_HPP

#include "IniFileObject.hpp"
#include "SearchList.hpp"

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

			void Clear();

			IniFileObject* GetObject(std::string key);
			IniFileObject* AddObject(std::string key, std::string value);
			void DeleteObject(std::string key);

			bool IsValid() const;

		private:
			Algorithm::SearchList<std::string,IniFileObject*> m_object;

			static IniFileSection s_sentinel;

			friend class IniFile;
		};
	}
}

#endif
