#include "TextureAtlasDataBase.hpp"

#include "Misc.hpp"
#include "Algorithm.hpp"
#include "Resources.hpp"
#include "Texture2D.hpp"

using namespace std;
using namespace MPACK;
using namespace MPACK::Algorithm;

namespace MPACK
{
	namespace Graphics
	{
		unordered_map<string, TextureInTexture> TextureAtlasDataBase::s_pathToAtlasMap;

		void TextureAtlasDataBase::Init()
		{
		}

		void TextureAtlasDataBase::Cleanup()
		{
			unordered_set<Texture2D*> textureToDelete;
			for(unordered_map<string, TextureInTexture>::iterator it=s_pathToAtlasMap.begin();it!=s_pathToAtlasMap.end();++it)
			{
				textureToDelete.insert(it->second.m_pTexture);
			}
			s_pathToAtlasMap.clear();

			for(unordered_set<Texture2D*>::iterator it=textureToDelete.begin();it!=textureToDelete.end();++it)
			{
				delete *it;
			}
			textureToDelete.clear();
		}

		void TextureAtlasDataBase::LoadAtlas(std::string pathToJSON, std::string pathToImage)
		{
			JSONParser parser;
			DOM *dom = parser.Load(pathToJSON);

			Texture2D *pTexture = new Texture2D();
			pTexture->Load(pathToImage, FILTER_BILINEAR);
			int atlasWidth = pTexture->GetWidth();
			int atlasHeight = pTexture->GetHeight();

			TextureInTexture texInTex;
			texInTex.m_pTexture = pTexture;

			for(SearchList<string,DOM*>::Iterator it=dom->Childs().Begin();it!=dom->Childs().End();++it)
			{
				string texPath = it->key;
				int x = StringEx::ToInt(it->value->Child("x")->GetValue());
				int y = StringEx::ToInt(it->value->Child("y")->GetValue());
				int width = StringEx::ToInt(it->value->Child("width")->GetValue());
				int height = StringEx::ToInt(it->value->Child("height")->GetValue());

				/*LOGD("texPath = %s", texPath.c_str());
				LOGD("x = %d",x);
				LOGD("y = %d",y);
				LOGD("width = %d",width);
				LOGD("height = %d",height);
*/
				texInTex.xMin = double(x) / double(atlasWidth - 1);
				texInTex.xMax = double(x + width - 1) / double(atlasWidth - 1);
				texInTex.yMin = 1.0 - double(y) / double(atlasHeight - 1);
				texInTex.yMax = 1.0 - double(y + height - 1) / double(atlasHeight - 1);

				s_pathToAtlasMap[texPath] = texInTex;
			}

			delete dom;
		}

		void TextureAtlasDataBase::LoadAtlases(std::string pathToJSON)
		{
			JSONParser parser;
			DOM *dom = parser.Load(pathToJSON);
			for(SearchList<string,DOM*>::Iterator it=dom->Childs().Begin();it!=dom->Childs().End();++it)
			{
				LoadAtlas(it->key, it->value->GetValue());
			}
			delete dom;
		}

		bool TextureAtlasDataBase::GetTexture(std::string pathToTexture, Texture2D* &texture, double &xMin, double &yMin, double &xMax, double &yMax)
		{
			unordered_map<string, TextureInTexture>::iterator it = s_pathToAtlasMap.find(pathToTexture);
			if (it != s_pathToAtlasMap.end())
			{
				texture = it->second.m_pTexture;
				xMin = it->second.xMin;
				xMax = it->second.xMax;
				yMin = it->second.yMin;
				yMax = it->second.yMax;
				return true;
			}
			return false;
		}
	}
}
