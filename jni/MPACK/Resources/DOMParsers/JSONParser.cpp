#include "JSONParser.hpp"

#include "DOM.hpp"
#include "Log.hpp"
#include "Resource.hpp"
#include "StringEx.hpp"

using namespace std;

namespace MPACK
{
	namespace Core
	{
		JSONParser::JSONParser()
		   : m_ptr(0), m_line(0), m_lastLine(0), m_ignoreWhitespace(true)
		{
		}

		JSONParser::~JSONParser()
		{
		}

		DOM* JSONParser::Load(std::string path)
		{
			Resource *res=LoadResource(path.c_str());
			res->Open();
			First((char*)res->Bufferize());
			DOM *dom=ParseRValue();
			delete res;
			return dom;
		}

		DOM* JSONParser::ParseRValue()
		{
			if(Char()=='{')
			{
				Next();

				bool firstObject=true;
				DOM *dom=new DOM();
				while(Char()!='}' && Char()!=0)
				{
					if(!firstObject)
					{
						if(Char()==',')
						{
							Next();
						}
						else
						{
							LOGW("JSONParser::ParserRValue() syntax error at line %d: expected ',' between keys",m_lastLine);
							delete dom;
							return DOM::GetSentinel();
						}
					}
					firstObject=false;

					string lValue = ParseLValue();

					if(Char()!=':')
					{
						LOGW("JSONParser::ParseRValue() syntax error at line %d: expected ':' after key",m_lastLine);
						delete dom;
						return DOM::GetSentinel();
					}
					Next();
					dom->m_childs[lValue]=ParseRValue();

					if(Char()!=',' && Char()!='}')
					{
						LOGW("JSONParser::ParseRValue() syntax error at line %d: expected ',' between keys or '}' after an object",m_lastLine);
						delete dom;
						return DOM::GetSentinel();
					}
				}
				if(Char()==0)
				{
					LOGW("JSONParser::ParseRValue() syntax error at line %d: expected '}' after an object",m_lastLine);
					delete dom;
					return DOM::GetSentinel();
				}
				Next();

				return dom;
			}
			else if(Char()=='"')
			{
				Next();
				string ans="";
				while(Char()!='"' && Char()!=0)
				{
					ans+=Char();
					Next();
				}
				if(Char()==0)
				{
					LOGW("JSONParser::ParseRValue() syntax error at line %d: expected '\"' after value",m_lastLine);
					return DOM::GetSentinel();
				}
				Next();

				return new DOM(ans,true);
			}
			LOGW("JSONParser::ParseRValue() syntax error at line %d: expected '{' or '\"' before an object",m_lastLine);
			return DOM::GetSentinel();
		}

		string JSONParser::ParseLValue()
		{
			if(Char()=='"')
			{
				string ans="";
				Next();
				while(Char()!='"' && Char()!=0)
				{
					ans+=Char();
					Next();
				}
				if(Char()==0)
				{
					LOGW("JSONParser::ParseLValue() syntax error at line %d: expected '\"' after key name",m_lastLine);
				}
				Next();
				return ans;
			}
			else
			{
				LOGW("JSONParser::ParseRValue() syntax error at line %d: expected '\"' before key name",m_lastLine);
			}
			return "";
		}

		void JSONParser::First(char *buffer)
		{
			m_ptr=buffer;
			m_ignoreWhitespace=true;
			m_line=1;

			while(StringEx::IsWhiteSpace(*m_ptr))
			{
				if(*m_ptr=='\n')
				{
					++m_line;
				}
				++m_ptr;
			}
		}

		void JSONParser::Next()
		{
			m_lastLine=m_line;
			if(*m_ptr==0)
			{
				return;
			}

			if(*m_ptr=='"')
			{
				m_ignoreWhitespace=!m_ignoreWhitespace;
			}

			++m_ptr;
			if(*m_ptr=='\n')
			{
				++m_line;
			}
			if(m_ignoreWhitespace)
			{
				while(StringEx::IsWhiteSpace(*m_ptr))
				{
					++m_ptr;
					if(*m_ptr=='\n')
					{
						++m_line;
					}
				}
			}
		}

		char JSONParser::Char()
		{
			return *m_ptr;
		}
	}
}

