#include "Game.h"

#include <sstream>

Game::Game()
{
}

void Game::run()
{
	//----Main Menu------------------//
	MainMenu *main_menu = new MainMenu;

	//------Screen setup------//
	sf::Vector2i screen_dimensions(screen_widht, screen_height);
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(screen_dimensions.x, screen_dimensions.y), "MPClient");
	window->setFramerateLimit(60);

	//------View setup------//
	sf::View *view = new sf::View(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
	view->setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	view->rotate(0);

	level_creation();

	begin_of_game = 0;
	_game_state = Game::showing_splash;

	//---after_death_timer---//
	time_passed_after_death = 60 * 10;

	score = 0;

	//----Scale
	SCALE = 40.f;

	player = new Player("box.png", 50, 500, 0.1f, SCALE);
	player1 = new Player("box.png", 50, 500, 0.1f, SCALE);
	ball = new Player("ball.png", 0, 0, 0.1f, SCALE);
	players.push_back(player);
	players.push_back(player1);
	players.push_back(ball);
	o_manager.add_object(player);
	o_manager.add_object(player1);
	o_manager.add_object(ball);

	//----Hit_Explosion_Animation----//
	sf::Texture animtexture;
	animtexture.loadFromFile("hit_explosion_animation.png");

	Animation explosion;
	explosion.setSpriteSheet(animtexture);

	for (int i = 0; i <= 12; i++)
	{
		explosion.addFrame(sf::IntRect(i * 256, 0, 256, 256));
	}

	currentAnimation = &explosion;

	animatedSprite.setFrameTime(sf::seconds(0.05f));
	animatedSprite.pause();
	animatedSprite.setLooped(false);
	animatedSprite.setOrigin(128, 128);
	//----Animation----//

	//----Explosion_Animation----//
	sf::Texture animtexture2;
	animtexture2.loadFromFile("animation_cloud_explosion_512.png");

	Animation explosion2;
	explosion2.setSpriteSheet(animtexture2);

	for (int i = 0; i <= 31; i++)
	{
		explosion2.addFrame(sf::IntRect(i * 512, 0, 512, 512));
	}

	currentAnimation2 = &explosion2;

	animatedSprite2.setFrameTime(sf::seconds(0.03f));
	animatedSprite2.pause();
	animatedSprite2.setLooped(false);
	//----Animation----//

	//----Shooting_Animation----//
	sf::Texture animtexture3;
	animtexture3.loadFromFile("turret_shooting_animation.png");

	Animation explosion3;
	explosion3.setSpriteSheet(animtexture3);

	for (int i = 0; i <= 35; i++)
	{
		explosion3.addFrame(sf::IntRect(i * 256, 0, 256, 256));
	}

	currentAnimation3 = &explosion3;
	animatedSprite3.setFrameTime(sf::seconds(0.03f));
	animatedSprite3.pause();
	animatedSprite3.setLooped(false);
	animatedSprite3.setOrigin(128, 128);

	// Declare and load a font
	font.loadFromFile("impact.ttf");

	gameloop(window, view, main_menu);
}

//-----Game_loop-----//
void Game::gameloop(sf::RenderWindow *window, sf::View *view, MainMenu *main_menu)
{
	while (!is_exiting())
	{
		sf::Event event;
		window->pollEvent(event);

		switch (_game_state)
		{
		case Game::showing_menu:
		{
			running = false;
			show_menu(window);
			break;
		}
		case Game::showing_splash:
		{
			running = false;
			show_splash_screen(window);
			break;
		}
		case Game::showing_game_over:
		{
			running = false;
			show_game_over(window);
			break;
		}
		case Game::playing:
		{
			running = true;
			window->clear(sf::Color(100, 200, 0));

			sf::Time elapsed = clock.restart();
			window->setView(*view);

			window->draw(map);
			window->draw(map2);
			o_manager.update(event, window, elapsed.asMilliseconds());
			o_manager.draw(window);

			////----Animations----//
			//animatedSprite.update(elapsed);
			//animatedSprite2.update(elapsed);
			//window->draw(animatedSprite);
			//window->draw(animatedSprite2);
			////----Animations----//

			//---Information_hud---//
			if (player->get_health() > 0)
			{
				// Create a text
				std::ostringstream re_text;
				re_text << "Score " << score;

				sf::Text text;
				text.setFont(font);
				text.setCharacterSize(100);
				text.setStyle(sf::Text::Bold);
				text.setColor(sf::Color::Yellow);
				text.setString(re_text.str());

				// Draw it
				window->setView(window->getDefaultView());
				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				text.setPosition(sf::Vector2f(screen_widht*0.2, (screen_height)*0.1));
				window->draw(text);
			}

			//Window Resized?
			if (event.type == sf::Event::Resized)
			{
				//The Window was Resized - Maintain Aspect Ratio
				float AspectX = (float)window->getSize().x / screen_widht;
				float AspectY = (float)window->getSize().y / screen_height;

				//Find Which Is the smaller aspect
				if (AspectX < AspectY)
				{
					//Resize Y To Fit
					sf::Vector2u tempSize = sf::Vector2u(window->getSize().x, (int)(AspectX * screen_height));
					window->setSize(tempSize);
				}
				else if (AspectX > AspectY)
				{
					//Resize X To Fit
					sf::Vector2u tempSize = sf::Vector2u((int)(AspectY * screen_widht), window->getSize().y);
					window->setSize(tempSize);
				}
			}

			//---Draw_display---//
			window->display();

			//---Score_during_playing---//
			break;
		}
		}

		if (event.type == sf::Event::Closed) _game_state = Game::exiting;

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape) show_menu(window);
		}

		//---wait_before_final_gameover---//
		if (player->get_health() <= 0)
		{
			time_passed_after_death--;

			if (time_passed_after_death <= 0)
			{
				show_game_over(window);
			}
		}
	}
	window->close();
}

void Game::level_creation()
{
	const int level[] =
	{
		0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
		0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3,
		3, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
		3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
		0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0,
		3, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 3, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
		0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
		3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0,
		0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
		0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3,
		3, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
		3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
		0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0,
		3, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 3, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
		0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
		3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0,
	};

	map.load("tileset_green_backround.png", sf::Vector2u(128, 128), level, 32, 32);
}

void Game::networkUpdate(int id, float x, float y, int r)
{
	players[id]->set_position(x, y);
	players[id]->set_rotation(r);
}

void Game::show_splash_screen(sf::RenderWindow *window)
{
	SplashScreen splash_screen;
	splash_screen.show(window);
	_game_state = Game::showing_menu;
}

void Game::show_menu(sf::RenderWindow *window)
{
	MainMenu main_menu;
	MainMenu::menu_result result = main_menu.show(window);
	switch (result)
	{
	case MainMenu::exit:
		std::cout << "Exit pressed" << std::endl;
		_game_state = exiting;
		break;
	case MainMenu::play:
		std::cout << "Play pressed" << std::endl;
		_game_state = playing;
		break;

	}
}

void Game::show_game_over(sf::RenderWindow *window)
{
	GameOver game_over;
	game_over.show(window);
	_game_state = exiting;
}

bool Game::is_exiting()
{
	if (_game_state == Game::exiting)
		return true;
	else
		return false;
}

Game::game_state Game::_game_state = uninitialized;
ObjectManager Game::o_manager;