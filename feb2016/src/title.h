#ifndef __TITLE_H
#define __TITLE_H

#include "screen.h"

class Title : public Screen
{
public:
	Title(InputDevice *inputDevice);
	virtual ~Title();

	void key_pressed(SDLKey key, SDLMod mod);
	void key_released(SDLKey key, SDLMod mod);

	void update();
	void move(double dt);
	void draw(Surface *dst);
private:
	Surface *m_titleSurface;
	int m_titleX;
	int m_titleY;
};

#endif
