#include "title.h"

#include "arena.h"
#include "resourcemanager.h"
#include "system.h"

Title::Title(InputDevice *inputDevice)
	:Screen(inputDevice),
	 m_titleSurface(NULL)
{
	ResourceManager *rm = ResourceManager::get_instance();
	m_titleSurface = rm->get_image("title.png");

	System *system = System::get_instance();
	int systemWidth = system->get_width();
	int systemHeight = system->get_height();
	
	int titleWidth = m_titleSurface->get_w();
	int titleHeight = m_titleSurface->get_h();

	m_titleX = (systemWidth - titleWidth) / 2;
	m_titleY = (systemHeight - titleHeight) / 4;
}

Title::~Title()
{
}

void Title::key_pressed(SDLKey, SDLMod)
{
}

void Title::key_released(SDLKey key, SDLMod)
{
	if (key == SDLK_z)
	{
		Arena *arena = new Arena(m_inputDevice, 1);
		transition(arena);
	}
	
	if (key == SDLK_x)
	{
		Arena *arena = new Arena(m_inputDevice, 2);
		transition(arena);
	}
	
	if (key == SDLK_c)
	{
		Arena *arena = new Arena(m_inputDevice, 3);
		transition(arena);
	}
}

void Title::update()
{
}

void Title::move(double)
{
}

void Title::draw(Surface *dst)
{
	dst->blit(m_titleSurface, m_titleX, m_titleY);

	ResourceManager *rm = ResourceManager::get_instance();
	Font *font = rm->get_font();

	int fontX = 150;
	int fontY = 280;
	int fontSkip = 20;
	font->draw_string(dst, fontX, fontY += fontSkip, "Z - NEW GAME [SMALL]");
	font->draw_string(dst, fontX, fontY += fontSkip, "X - NEW GAME [MEDIUM]");
	font->draw_string(dst, fontX, fontY += fontSkip, "C - NEW GAME [LARGE]");
	font->draw_string(dst, fontX, fontY += fontSkip, "ESC - QUIT");
}
