#ifndef MPACK_STRINGEX_HPP
#define MPACK_STRINGEX_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		namespace StringEx
		{
			extern const int PARAMETER_DEFAULT_VALUE;

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

			bool IsControl(const char &ch);
			bool IsPrintable(const char &ch);
			bool IsVisible(const char &ch);
			bool IsLowercase(const char &ch);
			bool IsUppercase(const char &ch);
			bool IsAlpha(const char &ch);
			bool IsDigit(const char &ch);
			bool IsXDigit(const char &ch);
			bool IsAlphaNumeric(const char &ch);
			bool IsWhiteSpace(const char &ch);
			bool IsPunctuation(const char &ch);

			int ToInt(const std::string &str);
			bool ToBool(const std::string &str);
			double ToDouble(const std::string &str);

			std::string StripLeft(std::string &str);
			std::string StripRight(std::string &str);
			std::string Strip(std::string &str);
			std::string Substr(std::string &str, int start, int length=-1);
			std::string Substring(std::string &str, int start, int end=PARAMETER_DEFAULT_VALUE);
			std::string Slice(std::string &str, int start, int end=PARAMETER_DEFAULT_VALUE);

			void MemSwap(char *pointer1, char *pointer2, int size);
		}
	}
}

#endif
