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

	boxTexture.loadFromFile("box.png");
	//--------------------------//

	//---death_image--//
	if (deathImage.loadFromFile("game_over.png") != true)
	{
		return;
	}

	game_over_sprite.setTexture(deathImage);
	//---after_death_timer---//
	time_passed_after_death = 60 * 10;

	score = 0;

	//---player_life_bar---//
	if (player_healtbar_texture.loadFromFile("box.png") != true)
	{
		return;
	}

	player_healtbar_sprite.setTexture(player_healtbar_texture);

	if (player_healtbar_texture_backround.loadFromFile("life_bar_back.png") != true)
	{
		return;
	}

	player_healtbar__backround_sprite.setTexture(player_healtbar_texture_backround);

	//----Scale
	SCALE = 30.f;

	player = new Player("box.png", 50, 500, 0.1f, SCALE);
	o_manager.add_object(player);

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

			player->get_position();

			////----Animations----//
			//animatedSprite.update(elapsed);
			//animatedSprite2.update(elapsed);
			//window->draw(animatedSprite);
			//window->draw(animatedSprite2);
			////----Animations----//

			//---Information_hud---//
			if (player->get_health() > 0)
			{
				// Declare and load a font
				sf::Font font;
				font.loadFromFile("impact.ttf");
				// Create a text
				std::ostringstream re_text;
				re_text << "Score " << score;

				sf::Text text;
				text.setFont(font);
				text.setCharacterSize(100);
				text.setStyle(sf::Text::Bold);
				text.setColor(sf::Color::Yellow);
				text.setString(re_text.str());

				font.loadFromFile("impact.ttf");
				// Create a text
				std::ostringstream he_text;
				he_text << "Health: ";

				sf::Text text2;
				text2.setFont(font);
				text2.setCharacterSize(50);
				text2.setStyle(sf::Text::Bold);
				text2.setColor(sf::Color::Red);
				text2.setString(he_text.str());

				// Create a text
				std::ostringstream f_text;
				f_text << "Fire!";

				sf::Text text3;
				text3.setFont(font);
				text3.setCharacterSize(50);
				text3.setStyle(sf::Text::Bold);
				text3.setColor(sf::Color::Magenta);
				text3.setString(f_text.str());

				// Draw it
				window->setView(window->getDefaultView());
				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				sf::FloatRect textRect2 = text2.getLocalBounds();
				text2.setOrigin(textRect2.left + textRect2.width / 2.0f,
					textRect2.top + textRect2.height / 2.0f);
				sf::FloatRect textRect3 = text3.getLocalBounds();
				text3.setOrigin(textRect3.left + textRect3.width / 2.0f,
					textRect3.top + textRect3.height / 2.0f);

				player_healtbar_sprite.setOrigin(sf::Vector2f(0, 20));
				player_healtbar_sprite.setPosition(screen_widht*0.14, screen_height*0.2);
				player_healtbar_sprite.setScale(sf::Vector2f(0.1*player->get_health(), 1));

				player_healtbar__backround_sprite.setOrigin(sf::Vector2f(0, 20));
				player_healtbar__backround_sprite.setPosition(screen_widht*0.14, screen_height*0.2);
				player_healtbar__backround_sprite.setScale(sf::Vector2f(0.1 * 100, 1));

				text.setPosition(sf::Vector2f(screen_widht*0.2, (screen_height)*0.1));
				text2.setPosition(sf::Vector2f(screen_widht*0.1, (screen_height)*0.2));
				text3.setPosition(sf::Vector2f(screen_widht*0.14 + 300, (screen_height)*0.25));
				window->draw(text);
				window->draw(text2);
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


	//Give me some trees...
	const int level_trees[] =
	{
		1, 2, 0, 3, 1, 1, 2, 0, 0, 1, 2, 2, 3, 1, 1, 1,
		2, 1, 0, 3, 0, 0, 2, 0, 0, 1, 2, 0, 3, 1, 0, 1,
		1, 1, 1, 1, 3, 3, 2, 0, 0, 3, 3, 3, 3, 2, 3, 1,
		3, 1, 0, 1, 1, 0, 1, 0, 0, 1, 2, 3, 3, 1, 0, 1,
		3, 2, 3, 3, 0, 0, 3, 0, 0, 3, 2, 3, 3, 3, 0, 1,
		1, 3, 0, 1, 1, 1, 3, 0, 0, 2, 1, 0, 1, 1, 3, 1,
		2, 2, 2, 3, 3, 0, 1, 0, 0, 2, 2, 1, 1, 1, 3, 1,
		1, 1, 0, 3, 1, 0, 1, 0, 0, 1, 2, 0, 3, 1, 0, 1,
		1, 2, 0, 3, 1, 1, 2, 0, 0, 1, 2, 2, 3, 1, 1, 1,
		2, 1, 0, 3, 0, 0, 2, 0, 0, 1, 2, 0, 3, 1, 0, 1,
		1, 1, 1, 1, 3, 3, 2, 0, 0, 3, 3, 3, 3, 2, 3, 1,
		3, 1, 0, 1, 1, 0, 1, 0, 0, 1, 2, 3, 3, 1, 0, 1,
		3, 2, 3, 3, 0, 0, 3, 0, 0, 3, 2, 3, 3, 3, 0, 1,
		1, 3, 0, 1, 1, 1, 3, 0, 0, 2, 1, 0, 1, 1, 3, 1,
		2, 2, 2, 3, 3, 0, 1, 0, 0, 2, 2, 1, 1, 1, 3, 1,
		1, 1, 0, 3, 1, 0, 1, 0, 0, 1, 2, 0, 3, 1, 0, 1,
	};

	map2.load("tileset_trees.png", sf::Vector2u(256, 256), level_trees, 16, 16);
}

void Game::networkUpdate(float x)
{
	player->set_position(x, 500);
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