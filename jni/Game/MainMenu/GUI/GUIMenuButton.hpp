#ifndef GUIMENUBUTTON_HPP
#define GUIMENUBUTTON_HPP

#include "Math.hpp"
#include "InputService.hpp"

#include <string>

using namespace std;
using namespace Math;

class GUIMenuButton
{
public:
	GUIMenuButton();

	string m_text;
	Vector2f m_pos,m_fixedPos,m_fingerStartPos;
	Core::Finger* m_pFinger;
	int m_id;
};

#endif
