#ifndef __MANAGER_H
#define __MANAGER_H

#include "input.h"
#include "menu.h"
#include "screen.h"

class Manager : public KeyListener, MouseListener
{
public:
	Manager();
	virtual ~Manager();

	void key_pressed(SDLKey key, SDLMod mod);
	void key_released(SDLKey key, SDLMod mod);
	void mouse_event(SDL_MouseButtonEvent event);

	void pause();
	void unpause();

	void update();
	void draw(Surface *dst);
private:
	MenuController *m_menu_controller;
	
	bool m_paused;
	Uint32 m_prev_move;
	Uint32 m_pause_ticks;

	InputDevice *m_key_device;
	InputDevice *m_joy_device;
	InputDevice *m_input_device;

	Screen *m_screen;
};

#endif
