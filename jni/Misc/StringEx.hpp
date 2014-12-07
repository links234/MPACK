#ifndef STRINGEX_HPP
#define STRINGEX_HPP

#include <string>

namespace Core
{
	namespace StringEx
	{
		const char* GetExtension(const char* pStr);
		void GetExtension(std::string path, std::string &ext);

		void Upper(std::string &str);
		void Lower(std::string &str);

		std::string ToUpper(std::string str);
		std::string ToLower(std::string str);

		void Upper(char &ch);
		void Lower(char &ch);

		char ToUpper(const char &ch);
		char ToLower(const char &ch);

		bool IsLowercase(const char &ch);
		bool IsUppercase(const char &ch);
		bool IsNumeric(const char &ch);
		bool IsAlphaNumeric(const char &ch);
		bool IsWhiteSpace(const char &ch);
	}
}

#endif
