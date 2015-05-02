#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class DOM;
	}
}

namespace MPACK
{
	namespace Core
	{
		class JSONParser : public Uncopyable
		{
		public:
			JSONParser();
			~JSONParser();

			DOM* Load(std::string path);
			void Save(std::string path, DOM* dom);

		private:
			DOM* ParseRValue();
			std::string ParseLValue();

			void First(char *buffer);
			void Next();
			char Char();

			char *m_ptr;
			int m_line;
			int m_lastLine;
			bool m_ignoreWhitespace;
		};
	}
}

#endif
