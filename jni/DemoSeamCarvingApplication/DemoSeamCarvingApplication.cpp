#include "DemoSeamCarvingApplication.hpp"

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
    img->Load("&img/test.png", false);
		Image *img2 = img->SeamCarvingDownsize(10, 100, Image::SeamCarvingType::GREEDY_PATH);
    img2->Save("img/test_random_sc.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;
		return 0;
	}
}
