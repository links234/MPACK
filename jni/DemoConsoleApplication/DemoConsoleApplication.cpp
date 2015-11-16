#include "DemoConsoleApplication.hpp"

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

		DOM *domTexture1Width = new DOM();
		domTexture1Width->SetValue("100 px");

		DOM *domTexture1Height = new DOM();
		domTexture1Height->SetValue("150 px");

		DOM *domTexture1 = new DOM();
		domTexture1->Childs().PushBack("width", domTexture1Width);
		domTexture1->Childs().PushBack("height", domTexture1Height);


		DOM *domTexture2Width = new DOM();
		domTexture2Width->SetValue("200 px");

		DOM *domTexture2Height = new DOM();
		domTexture2Height->SetValue("250 px");

		DOM *domTexture2 = new DOM();
		domTexture2->Childs().PushBack("width", domTexture2Width);
		domTexture2->Childs().PushBack("height", domTexture2Height);



		DOM *domTexInfo = new DOM();
		domTexInfo->Childs().PushBack("path/to/texture1", domTexture1);
		domTexInfo->Childs().PushBack("path/to/texture2", domTexture2);

		DOM *domDevWidth = new DOM();
		domDevWidth->SetValue("1900 px");

		DOM *domDevHeight = new DOM();
		domDevHeight->SetValue("1080 px");

		DOM *domGlobal = new DOM();
		domGlobal->Childs().PushBack("dev-width", domDevWidth);
		domGlobal->Childs().PushBack("dev-height", domDevHeight);
		domGlobal->Childs().PushBack("tex-info", domTexInfo);

		DOM *domTargetSmall = new DOM();
		domTargetSmall->Childs().PushBack("width", new DOM("1024", true));
		domTargetSmall->Childs().PushBack("height", new DOM("768", true));

		DOM *domTargetNormal = new DOM();
		domTargetNormal->Childs().PushBack("width", new DOM("1900", true));
		domTargetNormal->Childs().PushBack("height", new DOM("1080", true));

		DOM *domTargets = new DOM();
		domTargets->Childs().PushBack("small", domTargetSmall);
		domTargets->Childs().PushBack("normal", domTargetNormal);

		DOM *dom = new DOM();
		dom->Childs().PushBack("global", domGlobal);
		dom->Childs().PushBack("targets", domTargets);

		JSONParser jsonParser;
		jsonParser.Save("assets/local/save_pretty.json", dom, JSONParser::STYLE_MINIFIY);

		return 0;
	}
}
