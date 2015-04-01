#ifndef GUIMENU_HPP
#define GUIMENU_HPP

#include "MPACK.hpp"

#include "MMInputController.hpp"
#include "GUIMenuButton.hpp"

#include <vector>

using namespace std;

class GUIMenu
{
public:
	GUIMenu();
	~GUIMenu();

	int Update(GLfloat timeStep);
	void Render();

	void AddButton(string text, int id);
	void BuildLayout();

	static void DOWNEvent(void *pointer1, void *pointer2);
	static void UPEvent(void *pointer1, void *pointer2);

	MPACK::Graphics::Sprite *m_sprite;
private:
	vector<GUIMenuButton*> m_button;

	MMInputController *m_pMMInputController;

	int action;
};

#endif
