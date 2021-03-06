#ifndef MPACK_TEXTUREATLASDATABASE_HPP
#define MPACK_TEXTUREATLASDATABASE_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Texture2D;
	}
}

namespace MPACK
{
	namespace Graphics
	{
		struct TextureInTexture
		{
			Texture2D *m_pTexture;
			double xMin, xMax, yMin, yMax;
			int width, height;
		};

		class TextureAtlasDataBase
		{
		public:
			static void Init();
			static void Cleanup();

			static void StartLoadAtlasesProcess(std::string pathToJson);
			static bool ContinueLoadingProcess();

			static void LoadAtlas(std::string pathToJSON, std::string pathToImage);
			static void LoadAtlases(std::string pathToJSON);

			static bool GetTexture(std::string pathToTexture, Texture2D* &texture, double &xMin, double &yMin, double &xMax, double &yMax, int &width, int &height);

		private:
			static std::unordered_map<std::string, TextureInTexture> s_pathToAtlasMap;

			static int s_loadingProcessState;
			static std::vector<std::pair<std::string,std::string> > s_loadingProcessAtlases;
		};
	}
}

#endif
