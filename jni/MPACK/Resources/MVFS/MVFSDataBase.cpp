#include "MVFSDataBase.hpp"

#include "Types.hpp"
#include "MVFS.hpp"
#include "FileReaderInterface.hpp"
#include "FileReaderMPACK.hpp"

using namespace std;
using namespace MVFS;

namespace MPACK
{
	namespace Core
	{
		namespace MVFSDB
		{
			const int MAX_READERS = 32;

			static Reader *g_pReader[MAX_READERS];
			static FileReaderInterface *g_pFileReader[MAX_READERS];

			void Init()
			{
				for(int i=0;i<MAX_READERS;++i)
				{
					g_pReader[i] = NULL;
					g_pFileReader[i] = NULL;
				}
			}

			void Load(int id, const char *pPath, vector<char> key)
			{
				if(id < 0 || id > MAX_READERS)
				{
					return;
				}

				if(g_pReader[id])
				{
					delete g_pReader[id];
					g_pReader[id] = NULL;

					delete g_pFileReader[id];
					g_pFileReader[id] = NULL;
				}

				g_pFileReader[id] = FileReaderMPACK::Open(pPath);
				g_pReader[id] = Reader::Open(g_pFileReader[id], key);
			}

			Reader* Get(int id)
			{
				if(0<=id && id<MAX_READERS)
				{
					return g_pReader[id];
				}
				return NULL;
			}

			void Delete(int id)
			{
				if(0<=id && id<MAX_READERS)
				{
					if(g_pReader[id])
					{
						delete g_pReader[id];
						g_pReader[id] = NULL;

						delete g_pFileReader[id];
						g_pFileReader[id] = NULL;
					}
				}
			}

			void Clean()
			{
				for(int i=0;i<MAX_READERS;++i)
				{
					if(g_pReader[i])
					{
						delete g_pReader[i];
						g_pReader[i] = NULL;

						delete g_pFileReader[i];
						g_pFileReader[i] = NULL;
					}
				}
			}
		}
	}
}
