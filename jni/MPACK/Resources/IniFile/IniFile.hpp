#ifndef MPACK_INIFILE_HPP
#define MPACK_INIFILE_HPP

#include "Types.hpp"

#include "SearchList.hpp"
#include "IniFileSection.hpp"

namespace MPACK
{
	namespace Core
	{
		class IniFile
		{
		public:
			IniFile();
			~IniFile();

			void Clear();

			void Load(const char *pPath);
			void Save(const char *pPath);

			IniFileSection* GetSection(std::string section);
			IniFileSection* AddSection(std::string section);
			void DeleteSection(std::string section);

			IniFileObject* GetObject(std::string key);
			IniFileObject* AddObject(std::string key, std::string value);
			void DeleteObject(std::string key);

		private:
			std::string OutputBackspace(const std::string &text) const;

			Algorithm::SearchList<std::string,IniFileSection*> m_section;

			IniFileSection m_globalSection;
		};
	}
}

#endif
