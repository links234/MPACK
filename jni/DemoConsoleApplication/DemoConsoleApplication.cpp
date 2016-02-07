#include "DemoConsoleApplication.hpp"

using namespace MPACK::Graphics;

namespace Demo
{
	ConsoleApplication::ConsoleApplication()
	{
	}

	ConsoleApplication::~ConsoleApplication()
	{
	}

	int ConsoleApplication::Main()
	{
		LOGI("Demo::ConsoleApplication is working!!!");
		LOGD("Demo::ConsoleApplication has a bug!");
		LOGW("Demo::ConsoleApplication this should not be happening, falling back to older version!");
		LOGE("Demo::ConsoleApplication error, could not recover");

		DOM *domTexture1 = new DOM();
		domTexture1->AddString("width", "100 px");
		domTexture1->AddString("height", "150 px");

		DOM *domTexture2 = new DOM();
		domTexture2->AddString("width", "200 px");
		domTexture2->AddString("height", "250 px");

		DOM *domTexInfo = new DOM();
		domTexInfo->Childs().PushBack("path/to/texture1", domTexture1);
		domTexInfo->Childs().PushBack("path/to/texture2", domTexture2);

		DOM *domGlobal = new DOM();
		domGlobal->AddString("dev-width", "1900 px");
		domGlobal->AddString("dev-height", "1080 px");
		domGlobal->Childs().PushBack("tex-info", domTexInfo);

		DOM *domTargetSmall = new DOM();
		domTargetSmall->AddString("width", "1024");
		domTargetSmall->AddString("height", "768");

		DOM *domTargetNormal = new DOM();
		domTargetNormal->AddString("width", "1900");
		domTargetNormal->AddString("height", "1080");

		DOM *domTargets = new DOM();
		domTargets->Childs().PushBack("small", domTargetSmall);
		domTargets->Childs().PushBack("normal", domTargetNormal);

		DOM *dom = new DOM();
		dom->Childs().PushBack("global", domGlobal);
		dom->Childs().PushBack("targets", domTargets);

		JSONParser jsonParser;
		jsonParser.Save("assets/local/save_pretty.json", dom, JSONParser::STYLE_PRETTY);
		jsonParser.Save("assets/local/save_minify.json", dom, JSONParser::STYLE_MINIFIY);

		Image *img = new Image;
		img->InitColor(5000,5000,Color(255,255,255,0));
		Image *imgArrow = new Image;
		imgArrow->Load("@Sprites/Cursor.png", false);
		img->Blit(imgArrow, 100, 100);

		imgArrow->Save("assets/local/test2.png");
		delete imgArrow;

		img->Save("assets/local/test.png");
		delete img;
		return 0;
	}
}
