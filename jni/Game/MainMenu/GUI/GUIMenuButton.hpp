#ifndef GUIMENUBUTTON_HPP
#define GUIMENUBUTTON_HPP

#include "MPACK.hpp"

#include <string>

using namespace std;

class GUIMenuButton
{
public:
	GUIMenuButton();

	string m_text;
	MPACK::Math::Vector2f m_pos,m_fixedPos,m_fingerStartPos;
	MPACK::Input::Finger* m_pFinger;
	int m_id;
};

#endif
