#include "MainMenu.h"
#include <iostream>

MainMenu::menu_result MainMenu::show(sf::RenderWindow* win)
{
	sf::Texture image;
	image.loadFromFile("menu_screen.png");
	sf::Sprite sprite(image);

	//Play menu item coordinates
	menu_item play_button;
	play_button.rect.top = 145;
	play_button.rect.width = 380;
	play_button.rect.left = 0;
	play_button.rect.height = 1023;
	play_button.action = play;

	//Exit menu item coordinates
	menu_item exit_button;
	exit_button.rect.left = 0;
	exit_button.rect.height = 1023;
	exit_button.rect.top = 383;
	exit_button.rect.width = 560;
	
	exit_button.action = exit;

	menu_items.push_back(play_button);
	menu_items.push_back(exit_button);
			
	win->setView(win->getDefaultView());
	win->draw(sprite);
	win->display();

	return get_menu_response(win, &sprite);
}

MainMenu::menu_result MainMenu::handle_click(int x, int y)
{
	std::list<menu_item>::iterator it;
	for (it = menu_items.begin(); it != menu_items.end(); it++)
	{
		sf::Rect<int> menu_item_rect = (*it).rect;
		if (menu_item_rect.width > y
			&& menu_item_rect.top < y
			&& menu_item_rect.left < x
			&& menu_item_rect.height > x)
		{
			return (*it).action;
		}
	}

	return none;
}

MainMenu::menu_result MainMenu::get_menu_response(sf::RenderWindow* win, sf::Sprite* sprite)
{
	sf::Event menu_event;

	while (42 != 43)
	{

		while (win->pollEvent(menu_event))
		{
			//Window Resized?
			if (menu_event.type == sf::Event::Resized)
			{
				//The Window was Resized - Maintain Aspect Ratio
				float AspectX = (float)win->getSize().x / 1280;
				float AspectY = (float)win->getSize().y / 720;

				//Find Which Is the smaller aspect
				if (AspectX < AspectY)
				{
					//Resize Y To Fit
					sf::Vector2u tempSize = sf::Vector2u(win->getSize().x, (int)(AspectX * 720));
					win->setSize(tempSize);
				}
				else if (AspectX > AspectY)
				{
					//Resize X To Fit
					sf::Vector2u tempSize = sf::Vector2u((int)(AspectY * 1280), win->getSize().y);
					win->setSize(tempSize);
				}
			}

			win->draw(*sprite);
			win->display();

			if (menu_event.type == sf::Event::MouseButtonPressed)
			{
				//return handle_click(menu_event.mouseButton.x, menu_event.mouseButton.y);
			}
			if (menu_event.type == sf::Event::Closed)
			{
				return exit;
			}
			if (menu_event.type == sf::Event::KeyPressed)
			{
				if (menu_event.key.code == sf::Keyboard::Return)
				{
					return play;
				}
				if (menu_event.key.code == sf::Keyboard::Escape)
				{
					return exit;
				}
			}
		}
	}
}