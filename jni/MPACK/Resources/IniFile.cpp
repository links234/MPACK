#include "IniFile.hpp"

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
		}

		void IniFile::Load(const char *pPath)
		{
			Resource *pResource = LoadResource(pPath);
			ResourceReader reader(pResource);

			enum ParserState{Default, InComment, Backslash, Section, LeftValue, RightValue};

			ParserState state=Default;

			string lValue,rValue;

			while(!reader.EndOfFile())
			{
				char ch=reader.Char();

				switch(state)
				{
					case Default:

					break;
					case InComment:
						if(ch=='\n')
						{
							state=Default;
						}
					break;
					case Backslash:

					break;
					case Section:

					break;
					case LeftValue:

					break;
					case RightValue:

					break;
				}
			}

			delete pResource;
		}

		void IniFile::Save(const char *pPath)
		{
		}
	}
}
