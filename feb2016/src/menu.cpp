#include "menu.h"

#include "resourcemanager.h"
#include "system.h"

MenuController::MenuController()
	:m_menu(NULL),
	 m_old_menu(NULL)
{
}

MenuController::~MenuController()
{
	exit_all();
	if (m_old_menu != NULL)
		delete m_old_menu;
}

void MenuController::update()
{
	if (m_menu != NULL)
	{
		m_menu->update();
		m_menu->set_active(true);
	}

	if (m_old_menu != NULL)
	{
		delete m_old_menu;
		m_old_menu = NULL;
	}
}

void MenuController::draw(Surface *dst) const
{
	if (m_menu != NULL)
		m_menu->draw(dst);
}

Menu *MenuController::set_menu(Menu *menu)
{
	Menu *ret = m_menu;
	if (m_menu != NULL)
		m_menu->set_active(false);
	m_menu = menu;
	return ret;
}

void MenuController::exit_menu()
{
	/*
	fprintf(stderr, "exit_menu(%x)\n", m_menu);
	fflush(stderr);
	*/
	
	m_old_menu = m_menu;
	m_menu = m_menu->get_parent();
	if (m_menu != NULL)
		m_menu->reset();
}

void MenuController::exit_all()
{
	Menu *top_menu = m_menu;
	
	while (m_menu != NULL)
	{
		exit_menu();
		if (m_old_menu != top_menu)
			delete m_old_menu;
	}
	
	m_old_menu = top_menu;
}



Menu::Menu(MenuController *controller,
           InputDevice *device)
	:InputListener(device),
	 m_controller(controller),
	 m_parent(NULL),
	 m_active(true),
	 m_options(),
	 m_cur(0),
	 m_select_timer(0),
	 m_icon(NULL),
	 m_corner_x(0),
	 m_corner_y(0)
{
	m_parent = m_controller->set_menu(this);
	/*
	fprintf(stderr, "m_parent = %x\n", m_parent);
	fflush(stdout);
	*/
	
	ResourceManager *rm = ResourceManager::get_instance();
	m_icon = rm->get_image("interface/menu_icon.png");
}

Menu::~Menu()
{
}

void Menu::set_corner(int x, int y)
{
	m_corner_x = x;
	m_corner_y = y;
}

void Menu::reset()
{
	m_cur = 0;
}

void Menu::update()
{
	if (!m_active)
		return;

	/*
	if (m_select_timer.done())
	{
		int prev_cur = m_cur;
		
		int size = m_options.size();
		if (m_input->pressed(BUTTON_UP))
			m_cur = (m_cur + size - 1) % size;
		else if (m_input->pressed(BUTTON_DOWN))
			m_cur = (m_cur + size + 1) % size;

		if (prev_cur != m_cur)
		{
			DataManager *dm = DataManager::get_instance();
			double delay = dm->get_dbl("player_select_delay");
			m_select_timer.reset(delay);
		}
	}
	*/
}

void Menu::draw(Surface *dst) const
{
	ResourceManager *rm = ResourceManager::get_instance();
	Font *font = rm->get_font();

	int option_space = 5;
	int icon_space = 10;

	for (unsigned int i = 0; i < m_options.size(); ++i)
	{
		int str_x = m_corner_x;
		int str_y = m_corner_y + i * (font->get_h() + option_space);
		font->draw_string(dst, str_x, str_y, m_options[i].c_str());
	}

	int icon_x = m_corner_x - m_icon->get_w() - icon_space;
	int icon_y = m_corner_y + m_cur * (font->get_h() + option_space);
	dst->blit(m_icon, icon_x, icon_y);
}

void Menu::button_pressed(Button button)
{
	if (!m_active)
		return;
	
	if (button == BUTTON_SELECT ||
	    button == BUTTON_PAUSE)
		selection(m_options[m_cur]);
}



MainMenu::MainMenu(MenuController *menu_controller, InputDevice *device)
	:Menu(menu_controller, device)
{
	m_options.push_back("New Game");
	m_options.push_back("Instructions");
	m_options.push_back("Exit");

	set_corner(0, 0);
}

MainMenu::~MainMenu()
{
}

void MainMenu::selection(const string &option)
{
	fprintf(stderr, "MainMenu::selection(%s)\n", option.c_str());
	fflush(stderr);

	if (option == "New Game") printf("New game!!!!\n");
	else if (option == "Instructions") printf("Play by magic!\n");
	else if (option == "Exit")
	{
		m_controller->exit_menu();
		System *system = System::get_instance();
		system->exit();
	}
}
