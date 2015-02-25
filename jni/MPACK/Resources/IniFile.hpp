#ifndef MPACK_INIFILE_HPP
#define MPACK_INIFILE_HPP

#include "Types.hpp"

#include <string>

namespace MPACK
{
	namespace Core
	{
		class IniFile
		{
		public:
			IniFile();
			~IniFile();

			void Load(const char *pPath);
			void Save(const char *pPath);

		private:
			std::unordered_map<std::string,std::string> H;
		};
	}
}

#endif
