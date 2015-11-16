#ifndef MPACK_JSONPARSER_HPP
#define MPACK_JSONPARSER_HPP

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
			enum Style { STYLE_MINIFIY, STYLE_PRETTY };

			JSONParser();
			~JSONParser();

			DOM* Load(std::string path);
			void Save(std::string path, DOM* dom, Style style = STYLE_PRETTY);

		private:
			DOM* ParseRValue();
			std::string ParseLValue();

			void First(char *buffer);
			void Next();
			char Char();

			void Save_Minify(DOM *dom);
			void Save_Pretty(DOM *dom);
			void Save_PrettyPrefix();

			char *m_ptr;
			int m_line;
			int m_lastLine;
			bool m_ignoreWhitespace;

			std::ofstream m_output;
			int m_level;
		};
	}
}

#endif
