#include "manager.h"

#include "regionbuilder.h"
#include "resourcemanager.h"
#include "system.h"
#include "title.h"

Manager::Manager()
	:m_menu_controller(NULL),
	 m_paused(false),
	 m_prev_move(SDL_GetTicks()),
	 m_pause_ticks(0),
	 m_key_device(NULL),
	 m_joy_device(NULL),
	 m_input_device(NULL)
{
	System *system = System::get_instance();
	system->add_key_listener(this);
	system->add_mouse_listener(this);

	system->show_cursor(0);

	m_key_device = new KeyboardInput();
	//m_joy_device = new JoystickInput();
	m_input_device = m_key_device;

	//m_menu_controller = new MenuController();
	//new MainMenu(m_menu_controller, m_input_device);

	m_screen = new Title(m_input_device);
}

Manager::~Manager()
{
	delete m_screen;
	
	System *system = System::get_instance();
	system->remove_key_listener(this);
	system->remove_mouse_listener(this);

	//delete m_menu_controller;

	delete m_key_device;
	//delete m_joy_device;
}

void Manager::key_pressed(SDLKey key, SDLMod)
{
	if (key == SDLK_p)
	{
		if (m_paused)
			unpause();
		else
			pause();
	}
}

void Manager::key_released(SDLKey, SDLMod)
{
}

void Manager::mouse_event(SDL_MouseButtonEvent)
{
}

void Manager::pause()
{
	m_paused = true;
	/*
	  new PauseMenu(m_menu_controller,
	  m_input_device,
	  m_level_selector);
	*/
	m_pause_ticks = SDL_GetTicks() - m_prev_move;
}

void Manager::unpause()
{
	m_paused = false;
	m_prev_move = SDL_GetTicks() - m_pause_ticks;
	m_pause_ticks = 0;
}

void Manager::update()
{
	//Menu *menu = m_menu_controller->get_menu();

	//m_menu_controller->update();
	
	if (m_paused)
		return;

	/*
	  if (menu == NULL)
	  {
	  if (level->get_option("title"))
	  new MainMenu(m_menu_controller,
	  m_input_device,
	  m_level_selector);
	  }
	*/

	if (m_screen->isDone())
	{
		Screen *oldScreen = m_screen;
		m_screen = oldScreen->getNextScreen();
		delete oldScreen;
	}

	m_screen->update();
	
	Uint32 cur_time = SDL_GetTicks();
	double dt = (cur_time - m_prev_move) / 1000.0;
	dt = min(dt, 0.05);
	m_prev_move = cur_time;

	m_screen->move(dt);
}

void Manager::draw(Surface *dst)
{
	/*
	if (m_paused)
		dst->blit(m_pause, 0, 0);
	*/

	m_screen->draw(dst);

	//m_menu_controller->draw(dst);
}
