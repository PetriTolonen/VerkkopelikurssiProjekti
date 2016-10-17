#ifndef MAINMENU_H
#define MAINMENU_H

#include "IncludeHelper.h"
#include <list>

class MainMenu
{
public:
	enum menu_result{
		none,
		exit,
		play
	};

	struct menu_item
	{
	public:
		sf::Rect<int> rect;
		menu_result action;
	};

	menu_result show(sf::RenderWindow* win);
private:
	menu_result get_menu_response(sf::RenderWindow* win, sf::Sprite* sprite);
	menu_result handle_click(int x, int y);
	std::list<menu_item> menu_items;
};
#endif
