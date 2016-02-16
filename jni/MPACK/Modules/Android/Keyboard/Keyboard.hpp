#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <string>

namespace MPACK
{
	namespace SERVICES
	{
		namespace Keyboard
		{
			extern int hasToShow;

			void Init(int charLimit);
			void Show();
			void Hide();

			std::string GetText();
			void SetText(const std::string newText);
			bool IsVisible();

		}
	}
}



#endif
