#include "SplashScreen.h"


void SplashScreen::show(sf::RenderWindow* win)
{
	sf::Texture image;
	if (image.loadFromFile("splash_screen.png") != true)
	{
		return;
	}

	sf::Sprite sprite(image);

	win->draw(sprite);
	win->display();

	sf::Event event;
	while (true)
	{
		while (win->pollEvent(event))
		{
			//Window Resized?
			if (event.type == sf::Event::Resized)
			{
				//The Window was Resized - Maintain Aspect Ratio
				float AspectX = (float)win->getSize().x / 1920;
				float AspectY = (float)win->getSize().y / 1080;

				//Find Which Is the smaller aspect
				if (AspectX < AspectY)
				{
					//Resize Y To Fit
					sf::Vector2u tempSize = sf::Vector2u(win->getSize().x, (int)(AspectX * 1080));
					win->setSize(tempSize);
				}
				else if (AspectX > AspectY)
				{
					//Resize X To Fit
					sf::Vector2u tempSize = sf::Vector2u((int)(AspectY * 1920), win->getSize().y);
					win->setSize(tempSize);
				}
			}

			win->draw(sprite);
			win->display();

			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}
