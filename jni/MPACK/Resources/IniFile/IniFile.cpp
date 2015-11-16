#include "IniFile.hpp"

#include <fstream>

#include "Misc.hpp"
#include "InputResource.hpp"
#include "ResourceReader.hpp"

using namespace std;
using namespace MPACK::Algorithm;

namespace MPACK
{
	namespace Core
	{
		IniFile::IniFile()
		{
		}

		IniFile::~IniFile()
		{
			for(SearchList<string,IniFileSection*>::Iterator it=m_section.Begin();it!=m_section.End();++it)
			{
				delete it->value;
			}
		}

		void IniFile::Clear()
		{
			m_globalSection.Clear();

			for(SearchList<string,IniFileSection*>::Iterator it=m_section.Begin();it!=m_section.End();++it)
			{
				delete it->value;
			}
			m_section.Clear();
		}

		void IniFile::Load(const char *pPath)
		{
			Clear();

			InputResource *pInputResource = GetInputResource(pPath);
			pInputResource->Open();
			ResourceReader reader(pInputResource);

			enum ParserState{Default, InComment, Section, AfterSection, Backslash, LeftValue, RightValue};

			ParserState state=Default;
			ParserState previousState=Default;

			IniFileSection *pCurrentSection=&m_globalSection;

			string token;
			string previousToken;

			while(!reader.EndOfFile())
			{
				char ch=reader.CharNext();
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

			delete pInputResource;
		}

		void IniFile::Save(const char *pPath)
		{
			ofstream fout(pPath);
			for(SearchList<string,IniFileObject*>::Iterator it=m_globalSection.m_object.Begin();it!=m_globalSection.m_object.End();++it)
			{
				fout<<it->key<<"="<<OutputBackspace(it->value->GetValue())<<"\n";
			}
			fout<<"\n";
			for(SearchList<string,IniFileSection*>::Iterator it=m_section.Begin();it!=m_section.End();++it)
			{
				fout<<"["<<OutputBackspace(it->key)<<"]\n";
				for(SearchList<string,IniFileObject*>::Iterator itt=it->value->m_object.Begin();itt!=it->value->m_object.End();++itt)
				{
					fout<<itt->key<<"="<<OutputBackspace(itt->value->GetValue())<<"\n";
				}
				fout<<"\n";
			}
			fout.close();
		}

		IniFileSection* IniFile::GetSection(string section)
		{
			SearchList<string,IniFileSection*>::Iterator it=m_section.Find(section);
			if(it==m_section.End())
			{
				return &IniFileSection::s_sentinel;
			}
			return it->value;
		}

		IniFileSection* IniFile::AddSection(string section)
		{
			SearchList<string,IniFileSection*>::Iterator it=m_section.Find(section);
			if(it==m_section.End())
			{
				IniFileSection *pSection=new IniFileSection();
				m_section[section]=pSection;
				return pSection;
			}
			return it->value;
		}

		void IniFile::DeleteSection(string section)
		{
			m_section.Erase(section);
		}

		IniFileObject* IniFile::GetObject(string key)
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


		string IniFile::OutputBackspace(const string &text) const
		{
			string ans;
			for(int i=0;i<text.size();++i)
			{
				switch(text[i])
				{
					case '\\':
						ans+="\\\\";
					break;
					case '\0':
						ans+="\\0";
					break;
					case '\a':
						ans+="\\a";
					break;
					case '\b':
						ans+="\\b";
					break;
					case '\t':
						ans+="\\t";
					break;
					case '\r':
						ans+="\\r";
					break;
					case '\n':
						ans+="\\n";
					break;
					case ';':
						ans+="\\;";
					break;
					case '#':
						ans+="\\#";
					break;
					case '=':
						ans+="\\=";
					break;
					case ':':
						ans+="\\:";
					break;
					default:
						ans+=text[i];
					break;
				}
			}
			return ans;
		}
	}
}
