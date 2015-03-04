#ifndef MPACK_STRINGEX_HPP
#define MPACK_STRINGEX_HPP

#include <string>

namespace MPACK
{
	namespace Core
	{
		namespace StringEx
		{
			const char* GetExtension(const char* pStr);
			void GetExtension(std::string path, std::string &ext);

			std::string& Upper(std::string &str);
			std::string& Lower(std::string &str);

			std::string ToUpper(std::string str);
			std::string ToLower(std::string str);

			char& Upper(char &ch);
			char& Lower(char &ch);

			char ToUpper(const char &ch);
			char ToLower(const char &ch);

			bool IsLowercase(const char &ch);
			bool IsUppercase(const char &ch);
			bool IsNumeric(const char &ch);
			bool IsAlphaNumeric(const char &ch);
			bool IsWhiteSpace(const char &ch);

			std::string StripLeft(std::string &str);
			std::string StripRight(std::string &str);
			std::string Strip(std::string &str);
		}
	}
}

#endif
