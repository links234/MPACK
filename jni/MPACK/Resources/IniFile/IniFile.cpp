#include "IniFile.hpp"

#include "Misc.hpp"
#include "Resource.hpp"
#include "ResourceReader.hpp"

using namespace std;

namespace MPACK
{
	namespace Core
	{
		IniFile::IniFile()
		{
		}

		IniFile::~IniFile()
		{
			for(vector<IniFileSection*>::iterator it=m_sectionOrder.begin();it!=m_sectionOrder.end();++it)
			{
				delete *it;
			}
		}

		void IniFile::Clear()
		{
			m_globalSection.Clear();

			m_section.clear();
			for(vector<IniFileSection*>::iterator it=m_sectionOrder.begin();it!=m_sectionOrder.end();++it)
			{
				delete *it;
			}
			m_sectionOrder.clear();
		}

		void IniFile::Load(const char *pPath)
		{
			Clear();

			Resource *pResource = LoadResource(pPath);
			pResource->Open();
			ResourceReader reader(pResource);

			enum ParserState{Default, InComment, Section, AfterSection, Backslash, LeftValue, RightValue};

			ParserState state=Default;
			ParserState previousState=Default;

			IniFileSection *pCurrentSection=&m_globalSection;

			string token;
			string previousToken;

			while(!reader.EndOfFile())
			{
				char ch=reader.Char();
				switch(state)
				{
					case Default:
						if(ch=='\\')
						{
							previousState=LeftValue;
							state=Backslash;
						}
						else if(ch=='[')
						{
							token="";
							state=Section;
						}
						else if(ch==';' || ch=='#')
						{
							token="";
							state=InComment;
						}
						else if(ch=='=' || ch==':')
						{
							previousToken="";
							token="";
							state=RightValue;
						}
						else if(ch!='\n' && ch!='\r')
						{
							token="";
							token+=ch;
							state=LeftValue;
						}
					break;
					case InComment:
						if(ch=='\\')
						{
							state=Backslash;
							previousState=InComment;
						}
						else if(ch=='\n' || ch=='\r')
						{
							state=Default;
						}
						else
						{
							token+=ch;
						}
					break;
					case Section:
						if(ch=='\\')
						{
							state=Backslash;
							previousState=Section;
						}
						else if(ch==']')
						{
							token=StringEx::Strip(token);
							pCurrentSection=new IniFileSection;
							m_sectionOrder.push_back(pCurrentSection);
							m_section[token]=pCurrentSection;
							state=AfterSection;
						}
						else
						{
							token+=ch;
						}
					break;
					case AfterSection:
						if(ch=='\\')
						{
							state=Backslash;
							previousState=AfterSection;
						}
						else if(ch==';' || ch=='#')
						{
							state=InComment;
							token="";
						}
						else if(ch=='\n' || ch=='\r')
						{
							state=Default;
						}
					break;
					case Backslash:
						switch(ch)
						{
							case '\\':
								token+='\\';
							break;
							case '0':
								token+='\0';
							break;
							case 'a':
								token+='\a';
							break;
							case 'b':
								token+='\b';
							break;
							case 't':
								token+='\t';
							break;
							case 'r':
								token+='\r';
							break;
							case 'n':
								token+='\n';
							break;
							case ';':
								token+=';';
							break;
							case '#':
								token+='#';
							break;
							case '=':
								token+='=';
							break;
							case ':':
								token+=':';
							break;
						}
						state=previousState;
					break;
					case LeftValue:
						if(ch=='\\')
						{
							previousState=LeftValue;
							state=Backslash;
						}
						else if(ch=='=' || ch==':')
						{
							state=RightValue;
							previousToken=token;
							token="";
						}
						else if(ch=='\n' || ch=='\r')
						{
							state=Default;
						}
						else
						{
							token+=ch;
						}
					break;
					case RightValue:
						if(ch=='\\')
						{
							previousState=RightValue;
							state=Backslash;
						}
						else if(ch=='\n' || ch=='\r')
						{
							previousToken=StringEx::Strip(previousToken);
							token=StringEx::Strip(token);
							pCurrentSection->AddObject(previousToken,token);
							state=Default;
						}
						else if(ch==';' || ch=='#')
						{
							previousToken=StringEx::Strip(previousToken);
							token=StringEx::Strip(token);
							pCurrentSection->AddObject(previousToken,token);
							state=InComment;
							token="";
						}
						else
						{
							token+=ch;
						}
					break;
				}
			}

			delete pResource;
		}

		void IniFile::Save(const char *pPath)
		{
		}

		IniFileSection* IniFile::GetSection(string section) const
		{
			unordered_map<string,IniFileSection*>::const_iterator it=m_section.find(section);
			if(it==m_section.end())
			{
				return &IniFileSection::s_sentinel;
			}
			return it->second;
		}

		IniFileSection* IniFile::AddSection(string section)
		{
			unordered_map<string,IniFileSection*>::iterator it=m_section.find(section);
			if(it==m_section.end())
			{
				IniFileSection *pSection=new IniFileSection();
				m_section[section]=pSection;
				return pSection;
			}
			return it->second;
		}

		void IniFile::DeleteSection(string section)
		{
			unordered_map<string,IniFileSection*>::iterator it=m_section.find(section);
			if(it==m_section.end())
			{
				return;
			}
			int index=0;
			for(vector<IniFileSection*>::iterator it2=m_sectionOrder.begin();it2!=m_sectionOrder.end();++it2)
			{
				if(*it2==it->second)
				{
					delete *it2;
					swap(m_sectionOrder[index],m_sectionOrder[m_sectionOrder.size()-1]);
					m_sectionOrder.pop_back();
					return;
				}
				++index;
			}
		}

		IniFileObject* IniFile::GetObject(string key) const
		{
			return m_globalSection.GetObject(key);
		}

		IniFileObject* IniFile::AddObject(string key, string value)
		{
			return m_globalSection.AddObject(key,value);
		}

		void IniFile::DeleteObject(string key)
		{
			m_globalSection.DeleteObject(key);
		}
	}
}
