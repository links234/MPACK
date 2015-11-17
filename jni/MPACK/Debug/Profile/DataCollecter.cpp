#include "DataCollecter.hpp"

#include "Types.hpp"
#include "Render.hpp"
#include "Texture2D.hpp"

using namespace std;
using namespace MPACK::Graphics;

namespace MPACK
{
	namespace Profiler
	{
		struct TextureData
		{
			double screenWidth;
			double screenHeight;
		};

		std::unordered_map<string, TextureData> s_textureData;

		void RegisterCall_SpriteRender(Texture2D *pTexture,
				 	 	 	 	 	   double x, double y, double width, double height,
									   double minU, double maxU, double minV, double maxV)
		{
			TextureData textureData;
			textureData.screenWidth = width * (maxU - minU);
			textureData.screenHeight = height * (maxV - minV);
			s_textureData[pTexture->GetPath()] = textureData;
		}

		void GenerateMTexResizeJSON(string path)
		{
#if defined(LINUX_PLATFORM) || defined(WINDOWS_PLATFORM)
			ofstream fout(path);
			fout << "\"global\" : " << endl;
			fout << "{" << endl;
			fout << "\t\"dev-screen-width\" : " << Render::GetScreenWidth() << "," << endl;
			fout << "\t\"dev-screen-height\" : " << Render::GetScreenHeight() << "," << endl;
			fout << "\t\"tex-info\" :" << endl;
			fout << "\t{" << endl;
			for(unordered_map<string, TextureData>::iterator it=s_textureData.begin();it!=s_textureData.end();++it)
			{
				unordered_map<string, TextureData>::iterator itNext=it;
				++itNext;
				fout << "\t\t\"" << it->first << "\" : " << endl;
				fout << "\t\t{" << endl;
				fout << "\t\t\t\"dev-width\" : " << it->second.screenWidth << ", " << endl;
				fout << "\t\t\t\"dev-height\" : " << it->second.screenHeight << endl;
				if(itNext == s_textureData.end())
				{
					fout << "\t\t}" << endl;
				}
				else
				{
					fout << "\t\t}," << endl;
				}
			}
			fout << "\t}" << endl;
			fout << "}" << endl;
			fout.close();
#endif
		}
	}
}
