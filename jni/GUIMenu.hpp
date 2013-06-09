#ifndef GUIMENU_HPP
#define GUIMENU_HPP

#include "GUIMenuButton.hpp"
#include "Sprite.hpp"
#include "Global.hpp"
#include "Types.hpp"

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

	Sprite *m_sprite;
private:
	vector<GUIMenuButton*> m_button;

	int action;
};

#endif
