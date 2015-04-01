#ifdef ANDROID_PLATFORM

#ifndef MMANDROIDINPUT_HPP
#define MMANDROIDINPUT_HPP

#include "MMInputController.hpp"

class MMAndroidInput : public MMInputController
{
public:
	MMAndroidInput();
	virtual ~MMAndroidInput();

	virtual void Update(GLfloat delta);

private:
	static void DOWNEvent(void *pointer1, void *pointer2);
	static void UPEvent(void *pointer1, void *pointer2);
};

#endif

#endif
