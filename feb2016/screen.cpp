#include "screen.h"

#include "system.h"

Screen::Screen(InputDevice *inputDevice)
	:m_inputDevice(inputDevice),
	 m_nextScreen(NULL)
{
	System *system = System::get_instance();
	system->add_key_listener(this);
}

Screen::~Screen()
{
	System *system = System::get_instance();
	system->remove_key_listener(this);
}

void Screen::key_pressed(SDLKey, SDLMod)
{
}

void Screen::key_released(SDLKey, SDLMod)
{
}

void Screen::update()
{
}

void Screen::move(double)
{
}

void Screen::draw(Surface *)
{
}

void Screen::transition(Screen *nextScreen)
{
	if (m_nextScreen != NULL)
		delete m_nextScreen;
	m_nextScreen = nextScreen;
}
