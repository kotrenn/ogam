#include "input.h"

InputListener::InputListener(InputDevice *device)
	:m_input(device)
{
	m_input->add_input_listener(this);
}

InputListener::~InputListener()
{
	m_input->remove_input_listener(this);
}

void InputListener::button_pressed(Button) {}
void InputListener::button_released(Button) {}

void InputListener::set_input(InputDevice *device)
{
	m_input = device;
}



InputDevice::InputDevice()
	:m_listeners(),
	 m_listeners_add()
{
}

InputDevice::~InputDevice()
{
}

void InputDevice::synchronize()
{
	set<InputListener *>::iterator it;
	
	for (it = m_listeners_add.begin(); it != m_listeners_add.end(); it++)
		m_listeners.insert(*it);

	m_listeners_add.clear();
}

void InputDevice::add_input_listener(InputListener *listener)
{
	m_listeners_add.insert(listener);
}

void InputDevice::remove_input_listener(InputListener *listener)
{
	if (m_listeners.find(listener) != m_listeners.end())
		m_listeners.erase(listener);
}

void InputDevice::move_listeners(InputDevice *device)
{
	synchronize();
	
	set<InputListener *>::iterator it;
	for (it = m_listeners.begin(); it != m_listeners.end(); it++)
	{
		InputListener *listener = *it;
		remove_input_listener(listener);
		listener->set_input(device);
	}
}



KeyboardInput::KeyboardInput()
	:InputDevice(),
	 m_pressed()
{
	System *system = System::get_instance();
	system->add_key_listener(this);

	m_keys[BUTTON_UP]     = SDLK_UP;
	m_keys[BUTTON_DOWN]   = SDLK_DOWN;
	m_keys[BUTTON_LEFT]   = SDLK_LEFT;
	m_keys[BUTTON_RIGHT]  = SDLK_RIGHT;
	m_keys[BUTTON_SELECT] = SDLK_z;
	m_keys[BUTTON_PAUSE]  = SDLK_p;
}

KeyboardInput::~KeyboardInput()
{
	System *system = System::get_instance();
	system->remove_key_listener(this);
}

bool KeyboardInput::pressed(Button button)
{
	synchronize();
	
	if (m_pressed.find(button) == m_pressed.end())
		m_pressed[button] = false;
	return m_pressed[button];
}

void KeyboardInput::key_event(SDL_KeyboardEvent event)
{
	synchronize();
	
	SDL_keysym keysym = event.keysym;
	bool value = event.type == SDL_KEYDOWN;
	map<Button, SDLKey>::iterator it;
	set<InputListener *>::iterator li;
	for (it = m_keys.begin(); it != m_keys.end(); it++)
	{
		if (it->second == keysym.sym)
		{
			m_pressed[it->first] = value;
			for (li = m_listeners.begin(); li != m_listeners.end(); li++)
			{
				if (event.type == SDL_KEYDOWN)
					(*li)->button_pressed(it->first);
				else if (event.type == SDL_KEYUP)
					(*li)->button_released(it->first);
			}
		}
	}
}

void KeyboardInput::set_button(Button button, SDLKey key)
{
	m_keys[button] = key;
}
