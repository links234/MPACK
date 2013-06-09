#include "Misc.hpp"

namespace Misc
{
	const char* PathExtension(const char* pStr)
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

	void StringUpper(string &str)
	{
		for(register int i=0;i<str.size();++i)
		{
			if('a'<=str[i] || str[i]<='z')
			{
				str[i]+='A'-'a';
			}
		}
	}

	void StringLower(string &str)
	{
		for(register int i=0;i<str.size();++i)
		{
			if('A'<=str[i] || str[i]<='Z')
			{
				str[i]+='a'-'A';
			}
		}
	}

	void PathExtension(string path, string &ext)
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
}
