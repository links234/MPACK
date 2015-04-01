#ifndef MPACK_JSON_HPP
#define MPACK_JSON_HPP

#include "Types.hpp"

#include "SearchList.hpp"

namespace MPACK
{
	namespace Core
	{
		class JSON
		{
		public:
			JSON();
			~JSON();

			void Load(const char *pPath);
			void Save(const char *pPath);

		private:

		};
	}
}

#endif
