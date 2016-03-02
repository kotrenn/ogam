#ifndef __SCREEN_H
#define __SCREEN_H

#include "input.h"
#include "surface.h"

class Screen : public KeyListener
{
public:
	Screen(InputDevice *inputDevice);
	virtual ~Screen();

	bool isDone() { return m_nextScreen != NULL; }
	Screen *getNextScreen() { return m_nextScreen; }

	virtual void key_pressed(SDLKey key, SDLMod mod);
	virtual void key_released(SDLKey key, SDLMod mod);

	virtual void update();
	virtual void move(double dt);
	virtual void draw(Surface *dst);
protected:
	void transition(Screen *nextScreen);

	InputDevice *m_inputDevice;

private:
	Screen *m_nextScreen;
};

#endif
