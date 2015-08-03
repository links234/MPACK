#ifndef MPACK_MVFSDATABASE_HPP
#define MPACK_MVFSDATABASE_HPP

#include <vector>

namespace MVFS
{
	class Reader;
}

namespace MPACK
{
	namespace Core
	{
		namespace MVFSDB
		{
			void Init();
			void Load(int id, const char *pPath, std::vector<char> key=std::vector<char>());
			MVFS::Reader* Get(int id);
			void Delete(int id);
			void Clean();
		}
	}
}

#endif
