#include "GameOver.h"


void GameOver::show(sf::RenderWindow* win)
{
	sf::Texture image;
	if (image.loadFromFile("game_over.png") != true)
	{
		return;
	}

	sf::Sprite sprite(image);

	win->setView(win->getDefaultView());
	win->draw(sprite);
	win->display();

	sf::Event event;
	while (true)
	{
		while (win->pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}
