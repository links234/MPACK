#include "StringEx.hpp"

using namespace std;

namespace Core
{
	namespace StringEx
	{
		const char* GetExtension(const char* pStr)
		{
			const char* last=NULL;
			while(pStr)
			{
				++pStr;
				if(*pStr=='.')
				{
					last=pStr;
				}
			}
			if(!last)
			{
				last=pStr;
			}
			else
			{
				++last;
			}
			return last;
		}

		void GetExtension(string path, string &ext)
		{
			int i;
			ext="";
			for(i=path.size()-1;i>=0;--i)
			{
				if(path[i]=='.')
				{
					break;
				}
			}
			if(i>=0)
			{
				++i;
				for(;i<path.size();++i)
				{
					ext=ext+path[i];
				}
			}
		}

		void Upper(string &str)
		{
			for(int i=0;i<str.size();++i)
			{
				if('a'<=str[i] && str[i]<='z')
				{
					str[i]+='A'-'a';
				}
			}
		}

		void Lower(string &str)
		{
			for(int i=0;i<str.size();++i)
			{
				if('A'<=str[i] && str[i]<='Z')
				{
					str[i]+='a'-'A';
				}
			}
		}

		std::string ToUpper(std::string str)
		{
			for(int i=0;i<str.size();++i)
			{
				if('a'<=str[i] && str[i]<='z')
				{
					str[i]=str[i]-'a'+'A';
				}
			}
			return str;
		}

		std::string ToLower(std::string str)
		{
			for(int i=0;i<str.size();++i)
			{
				if('A'<=str[i] && str[i]<='Z')
				{
					str[i]=str[i]-'A'+'a';
				}
			}
			return str;
		}

		void Upper(char &ch)
		{
			if('a'<=ch && ch<='z')
			{
				ch=ch-'a'+'A';
			}
		}

		void Lower(char &ch)
		{
			if('A'<=ch && ch<='Z')
			{
				ch=ch-'A'+'a';
			}
		}

		char ToUpper(const char &ch)
		{
			if('a'<=ch && ch<='z')
			{
				return ch-'a'+'A';
			}
			return ch;
		}

		char ToLower(const char &ch)
		{
			if('A'<=ch && ch<='Z')
			{
				return ch-'A'+'a';
			}
		}
	}
}

