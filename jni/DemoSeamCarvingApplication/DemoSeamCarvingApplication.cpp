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
		Image *img;
		Image *img2;
/*
		//1.1
		img = new Image();
		img->Load("&img/castel.png", false);
		img2 = img->SeamCarvingDownsize(50, 0, Image::SeamCarvingType::RANDOM_PATH);
		img2->Save("img/results/castel_horizontal_downsize_50px_random.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(50, 0, Image::SeamCarvingType::GREEDY_PATH);
		img2->Save("img/results/castel_horizontal_downsize_50px_greedy.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(50, 0, Image::SeamCarvingType::BEST_PATH);
		img2->Save("img/results/castel_horizontal_downsize_50px_dp.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;

		// 1.2
		img = new Image();
		img->Load("&img/praga.png", false);
		img2 = img->SeamCarvingDownsize(0, 100, Image::SeamCarvingType::RANDOM_PATH);
		img2->Save("img/results/praga_vertical_downsize_100px_random.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(0, 100, Image::SeamCarvingType::GREEDY_PATH);
		img2->Save("img/results/praga_vertical_downsize_100px_greedy.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(0, 100, Image::SeamCarvingType::BEST_PATH);
		img2->Save("img/results/praga_vertical_downsize_100px_dp.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;

		// 1.3
		img = new Image();
		img->Load("&img/delfin.png", false);
		img2 = img->SeamCarvingUpsize(50, 50, Image::SeamCarvingType::BEST_PATH);
		img2->Save("img/results/delfin_upscale_50px_both.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;
*/
		// 1.4
		img = new Image();
		img->Load("&img/lac.png", false);

		vector<SeamCarvingEdit> modifiers;
		Image::SeamCarvingAddRectangleEnergyModifier(&modifiers, 465, 165, 100, 90, 1e9);
		Image::SeamCarvingAddRectangleEnergyModifier(&modifiers, 155, 175, 180 - 155, 272 - 175, 1e9);
		Image::SeamCarvingAddRectangleEnergyModifier(&modifiers, 75, 240, 240 - 75, 280 - 240, 1e9);
		Image::SeamCarvingAddRectangleEnergyModifier(&modifiers, 403, 175, 70, 60, -1e9);
		img2 = img->SeamCarvingDownsize(90, 0, Image::SeamCarvingType::BEST_PATH, &modifiers);
		img2->Save("img/results/lac_remove_girl_and_keep_picnic_horizontal_90px.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;
/*
		// 1.5
		img = new Image();
		img->Load("&img/1.png", false);
		LOGD("1");
		img2 = img->SeamCarvingDownsize(200, 0, Image::SeamCarvingType::RANDOM_PATH);
		LOGD("2");
		img2->Save("img/results/1_horizontal_downsize_200px_random.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(200, 0, Image::SeamCarvingType::GREEDY_PATH);
		img2->Save("img/results/1_horizontal_downsize_200px_greedy.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(200, 0, Image::SeamCarvingType::BEST_PATH);
		img2->Save("img/results/1_horizontal_downsize_200px_dp.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;

		img = new Image();
		img->Load("&img/2.png", false);
		img2 = img->SeamCarvingDownsize(150, 0, Image::SeamCarvingType::RANDOM_PATH);
		img2->Save("img/results/2_horizontal_downsize_150px_random.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(150, 0, Image::SeamCarvingType::GREEDY_PATH);
		img2->Save("img/results/2_horizontal_downsize_150px_greedy.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(150, 0, Image::SeamCarvingType::BEST_PATH);
		img2->Save("img/results/2_horizontal_downsize_150px_dp.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;

		img = new Image();
		img->Load("&img/3.png", false);
		img2 = img->SeamCarvingDownsize(150, 0, Image::SeamCarvingType::RANDOM_PATH);
		img2->Save("img/results/3_horizontal_downsize_150px_random.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(150, 0, Image::SeamCarvingType::GREEDY_PATH);
		img2->Save("img/results/3_horizontal_downsize_150px_greedy.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(150, 0, Image::SeamCarvingType::BEST_PATH);
		img2->Save("img/results/3_horizontal_downsize_150px_dp.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;

		img = new Image();
		img->Load("&img/4.png", false);
		img2 = img->SeamCarvingDownsize(200, 0, Image::SeamCarvingType::RANDOM_PATH);
		img2->Save("img/results/4_horizontal_downsize_200px_random.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(200, 0, Image::SeamCarvingType::GREEDY_PATH);
		img2->Save("img/results/4_horizontal_downsize_200px_greedy.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(200, 0, Image::SeamCarvingType::BEST_PATH);
		img2->Save("img/results/4_horizontal_downsize_200px_dp.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;

		img = new Image();
		img->Load("&img/5.png", false);
		img2 = img->SeamCarvingDownsize(200, 0, Image::SeamCarvingType::RANDOM_PATH);
		img2->Save("img/results/5_horizontal_downsize_200px_random.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(200, 0, Image::SeamCarvingType::GREEDY_PATH);
		img2->Save("img/results/5_horizontal_downsize_200px_greedy.png", Image::FileFormatType::PNG);
		delete img2;
		img2 = img->SeamCarvingDownsize(200, 0, Image::SeamCarvingType::BEST_PATH);
		img2->Save("img/results/5_horizontal_downsize_200px_dp.png", Image::FileFormatType::PNG);
		delete img2;
		delete img;
*/
		return 0;
	}
}
