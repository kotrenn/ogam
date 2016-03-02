#ifndef __MENU_H
#define __MENU_H

#include "input.h"
#include "surface.h"
#include "timer.h"

class Menu;

class MenuController
{
public:
	MenuController();
	~MenuController();

	void update();
	void draw(Surface *dst) const;
	
	Menu *get_menu() const { return m_menu; }
	Menu *set_menu(Menu *menu);
	void exit_menu();
	void exit_all();
private:
	Menu *m_menu;
	Menu *m_old_menu;
};

class Menu : public InputListener
{
public:
	Menu(MenuController *menu_controller,
	     InputDevice *device);
	virtual ~Menu();

	void set_corner(int x, int y);
	void reset();
	void update();
	void draw(Surface *dst) const;
	
	virtual void button_pressed(Button button);

	Menu *get_parent() const { return m_parent; }
	void set_active(bool active) { m_active = active; }
protected:
	virtual void selection(const string &option) = 0;

	MenuController *m_controller;
	Menu *m_parent;
	bool m_active;
	vector<string> m_options;
	int m_cur;
	Timer m_select_timer;
	Surface *m_icon;
	int m_corner_x;
	int m_corner_y;
};

class MainMenu : public Menu
{
public:
	MainMenu(MenuController *menu_controller, InputDevice *device);
	virtual ~MainMenu();
	
private:
	void selection(const string &option);
};

#endif
