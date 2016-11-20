#include "DemoSeamCarvingApplication.hpp"

using namespace std;
using namespace MPACK::Graphics;

namespace Demo
{
	SeamCarvingApplication::SeamCarvingApplication()
	{
	}

	SeamCarvingApplication::~SeamCarvingApplication()
	{
	}

	int SeamCarvingApplication::Main()
	{
    Image *img = new Image();
    img->Load("&img/lac.png", false);

		vector<SeamCarvingEdit> modifiers;
		Image::SeamCarvingAddRectangleEnergyModifier(&modifiers, 465, 165, 100, 90, 1e9);
		Image::SeamCarvingAddRectangleEnergyModifier(&modifiers, 155, 175, 180 - 155, 272 - 175, 1e9);
		Image::SeamCarvingAddRectangleEnergyModifier(&modifiers, 75, 240, 240 - 75, 280 - 240, 1e9);
		Image::SeamCarvingAddRectangleEnergyModifier(&modifiers, 405, 175, 420 - 405, 205 - 175, -1e9);
		Image *img2 = img->SeamCarvingDownsize(84, 0, Image::SeamCarvingType::BEST_PATH, &modifiers);
		img2->Save("img/lac_remove.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;
		return 0;
	}
}
