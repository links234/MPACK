#include "StringEx.hpp"

using namespace std;
using namespace MPACK::Math;

namespace MPACK
{
	namespace Core
	{
		namespace StringEx
		{
			const int PARAMETER_DEFAULT_VALUE=1<<30;

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

			string& Upper(string &str)
			{
				for(int i=0;i<str.size();++i)
				{
					if('a'<=str[i] && str[i]<='z')
					{
						str[i]+='A'-'a';
					}
				}
				return str;
			}

			string& Lower(string &str)
			{
				for(int i=0;i<str.size();++i)
				{
					if('A'<=str[i] && str[i]<='Z')
					{
						str[i]+='a'-'A';
					}
				}
				return str;
			}

			string ToUpper(std::string str)
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

			string ToLower(std::string str)
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

			char& Upper(char &ch)
			{
				if('a'<=ch && ch<='z')
				{
					ch=ch-'a'+'A';
				}
				return ch;
			}

			char& Lower(char &ch)
			{
				if('A'<=ch && ch<='Z')
				{
					ch=ch-'A'+'a';
				}
				return ch;
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

			bool IsControl(const char &ch)
			{
				return (0<=ch && ch<=31) || ch==127;
			}

			bool IsPrintable(const char &ch)
			{
				return !IsControl(ch);
			}

			bool IsVisible(const char &ch)
			{
				return IsPrintable(ch) && !IsWhiteSpace(ch);
			}

			bool IsLowercase(const char &ch)
			{
				return 'a'<=ch && ch<='z';
			}

			bool IsUppercase(const char &ch)
			{
				return 'A'<=ch && ch<='Z';
			}

			bool IsAlpha(const char &ch)
			{
				return ('A'<=ch && ch<='Z') || ('a'<=ch && ch<='z');
			}

			bool IsDigit(const char &ch)
			{
				return '0'<=ch && ch<='9';
			}

			bool IsXDigit(const char &ch)
			{
				return ('0'<=ch && ch<='9') || ('A'<=ch && ch<='F') || ('a'<=ch && ch<='f');
			}

			bool IsAlphaNumeric(const char &ch)
			{
				return ('0'<=ch && ch<='9') || ('a'<=ch && ch<='z') || ('A'<=ch && ch<='Z');
			}

			bool IsWhiteSpace(const char &ch)
			{
				return ch==' ' || ch=='\t' || ch=='\n' || ch=='\r' || ch=='\v' || ch=='\f';
			}

			bool IsPunctuation(const char &ch)
			{
				return !IsAlphaNumeric(ch) && IsVisible(ch);
			}


			bool ToInt(const string &str, int &number)
			{	
				if (str.size() == 0) return false;
				int i = 0;
				if (str[i] == '-' || str[i] == '+') 
				{
					if (str.size() == 1) return false;
					i++;
				}
				for (i = 0; i < str.size(); i++)
					if (!IsDigit(str[i]))
						return false;

				number = ToInt(str);
				return true;
			}

			int ToInt(const string &str)
			{
				int ans=0;
				int semn=1;
				int index=0;
				if(str[0]=='-')
				{
					semn=-1;
					++index;
				}
				else if(str[0]=='+')
				{
					++index;
				}
				for(;index<str.size();++index)
				{
					if(!('0'<=str[index] && str[index]<='9') )
					{
						return 0;
					}
					ans*=10;
					ans+=str[index]-'0';
				}
				return semn*ans;
			}

			bool ToBool(const string &str)
			{
				string ustr=ToUpper(str);
				if(ustr=="TRUE")
				{
					return true;
				}
				if(ustr=="T")
				{
					return true;
				}
				if(ustr=="Y")
				{
					return true;
				}
				if(ustr=="YES")
				{
					return true;
				}
				if(ustr=="1")
				{
					return true;
				}
				return false;
			}

			double ToDouble(const string &str)
			{
				double ans=0;
				double semn=1;
				int index=0;
				if(str[0]=='-')
				{
					semn=-1.0;
					++index;
				}
				else if(str[0]=='+')
				{
					++index;
				}
				double div=1.0;
				bool afterPoint=false;
				for(;index<str.size();++index)
				{
					if(str[index]=='.')
					{
						afterPoint=true;
					}
					else
					{
						if(afterPoint)
						{
							div*=10.0;
						}
						if(!('0'<=str[index] && str[index]<='9') )
						{
							return 0;
						}
						ans*=10.0;
						ans+=str[index]-'0';
					}
				}
				return semn*ans/div;
			}

			string StripLeft(string &str)
			{
				string ans;
				int i=0;
				for(;i<str.size();++i)
				{
					if(!IsWhiteSpace(str[i]))
					{
						break;
					}
				}
				for(;i<str.size();++i)
				{
					ans+=str[i];
				}
				return ans;
			}

			string StripRight(string &str)
			{
				int i=str.size()-1;
				for(;i>=0 && IsWhiteSpace(str[i]);--i);
				if(IsWhiteSpace(str[i]))
				{
					--i;
				}
				string ans=str;
				ans.resize(i+1);
				return ans;
			}

			string Strip(string &str)
			{
				string ans;
				int i=0;
				for(;i<str.size();++i)
				{
					if(!IsWhiteSpace(str[i]))
					{
						break;
					}
				}
				for(;i<str.size();++i)
				{
					ans+=str[i];
				}

				i=ans.size()-1;
				for(;i>=0 && IsWhiteSpace(ans[i]);--i);
				if(IsWhiteSpace(ans[i]))
				{
					--i;
				}
				ans.resize(i+1);
				return ans;
			}

			string Substr(string &str, int start, int length)
			{
				string ans;
				if(start<0)
				{
					start+=str.size();
				}
				if(start<0)
				{
					return ans;
				}
				int end;
				if(length==PARAMETER_DEFAULT_VALUE)
				{
					end=str.size();
				}
				else
				{
					end=start+length-1;
				}
				if(end>=str.size())
				{
					end=str.size()-1;
				}
				for(int i=start;i<=end;++i)
				{
					ans+=str[i];
				}
				return ans;
			}

			string Substring(string &str, int start, int end)
			{
				string ans;
				start=Math::Misc<int>::Clamp(start,0,str.size());
				end=Math::Misc<int>::Clamp(end,0,str.size());
				if(end==PARAMETER_DEFAULT_VALUE)
				{
					end=str.size();
				}
				if(start>end)
				{
					swap(start,end);
				}
				for(int i=start;i<end;++i)
				{
					ans+=str[i];
				}
				return ans;
			}

			string Slice(string &str, int start, int end)
			{
				string ans;
				if(end==PARAMETER_DEFAULT_VALUE)
				{
					end=str.size();
				}
				else if(end<0)
				{
					end=str.size()-1+end;
				}
				end=Math::Misc<int>::Clamp(end,0,str.size());
				start=Math::Misc<int>::Clamp(start,0,str.size());
				if(start<end)
				{
					for(int i=start;i<end;++i)
					{
						ans+=str[i];
					}
				}
				else
				{
					for(int i=start;i<str.size();++i)
					{
						ans+=str[i];
					}
					for(int i=0;i<end;++i)
					{
						ans+=str[i];
					}
				}
				return ans;
			}

			void MemSwap(char *pointer1, char *pointer2, int size)
			{
				for(int i=0;i<size;++i,++pointer1,++pointer2)
				{
					swap(*pointer1,*pointer2);
				}
			}
		}
	}
}
