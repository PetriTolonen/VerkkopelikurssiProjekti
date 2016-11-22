#include "Game.h"

#include <sstream>

Game::Game() :myWorld(b2Vec2(0.0f,0.0f))
{
}

void Game::run()
{
	//----Main Menu------------------//
	MainMenu *main_menu = new MainMenu;

	//------Screen setup------//
	sf::Vector2i screen_dimensions(screen_widht, screen_height);
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(screen_dimensions.x, screen_dimensions.y), "Tank Hunter Arcade");
	window->setFramerateLimit(60);

	//------View setup------//
	sf::View *view = new sf::View(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
	//view.reset(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
	view->setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	view->rotate(180);

	level_creation();

	map3.setPosition(0, 4096);
	map4.setPosition(0, 4096);

	level_move_count = 0;
	modulo_int = 0;

	begin_of_game = 0;
	_game_state = Game::showing_splash;

	//----Init
	//myWorld.Step(1.0f / 60.0f, 8, 4);

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

	//---cooldownbar---//
	if (cooldown_texture.loadFromFile("life_bar_back.png") != true)
	{
		return;
	}

	cooldown_sprite.setTexture(cooldown_texture);

	if (cooldown_texture_back.loadFromFile("box.png") != true)
	{
		return;
	}

	cooldown_sprite_back.setTexture(cooldown_texture_back);

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


	//---------Contact Listener-----------------//
	ContactListener = new MyContactListener();
	myWorld.SetContactListener(ContactListener);

	//----Scale
	SCALE = 30.f;

	//---player_b2_body---//	
	b2BodyDef BodyDef;
	//BodyDef.position = b2Vec2(2048.0f / SCALE, (screen_height / 2) / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* player_body = myWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((31.f) / SCALE, (66.f) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 10.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	player_body->SetUserData("player");
	player_body->CreateFixture(&FixtureDef);
	player_body->SetTransform(b2Vec2(2048.0 / SCALE, (screen_height / 2) / SCALE), 0);
	//Tank movement dampening
	player_body->SetLinearDamping(5);
	player_body->SetAngularDamping(10);


	Tank_hull hull("tank_hull", 1.2, 0.2, 1, 7, 1, 38000, 165);
	Tank_turret turret("tank_tower", 45, 1.4, 200);
	player = new Player(player_body, &hull, &turret, 0, 0, 0, 0, 0, 0, 0, 0);
	o_manager.add_object(player);

	ai_manager = new AiManager();

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
			show_menu(window);
			break;
		}
		case Game::showing_splash:
		{
			show_splash_screen(window);
			break;
		}
		case Game::showing_game_over:
		{
			show_game_over(window);
			break;
		}
		case Game::playing:
		{
			window->clear(sf::Color(100, 200, 0));

			sf::Time elapsed = clock.restart();
			set_view(view, player);

			myWorld.Step(1.0f / 60.0f, 8, 4);


			//-----------------Firing Main Gun--------------------------------------//

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->get_health() > 0)
			{
				if (player->get_can_fire() == true)
				{

					//--ammo_b2_body-----//

					b2Body* ammo_body;

					b2BodyDef ammoBodyDef;
					ammoBodyDef.position = b2Vec2((((player->get_position().x) + (-cos(player->get_rotation_turret() / (180.0f / b2_pi))) * 90) / SCALE), ((player->get_position().y) + (-sin(player->get_rotation_turret() / (180.0f / b2_pi))) * 90) / SCALE);
					ammoBodyDef.type = b2_kinematicBody;
					ammoBodyDef.bullet = true;

					ammo_body = myWorld.CreateBody(&ammoBodyDef);

					b2PolygonShape shape_ammo;
					shape_ammo.SetAsBox((10.f) / SCALE, (5.f) / SCALE);
					b2FixtureDef AmmoFixtureDef;

					AmmoFixtureDef.shape = &shape_ammo;
					ammo_body->SetUserData("ammo");
					ammo_body->CreateFixture(&AmmoFixtureDef);

					//------------------------//

					Ammo *round = new Ammo("ammo", ammo_body, 12.0f, 1.0, 3.0, player->get_position().x, player->get_position().y);

					float x = 0;
					float y = 0;


					x = round->get_velocity() * (-cos(player->get_rotation_turret() / (180.0f / b2_pi)));
					y = round->get_velocity() * (-sin(player->get_rotation_turret() / (180.0f / b2_pi)));

					round->set_velocity(x, y);
					round->set_rotation(player->get_rotation_turret() / (180.0f / b2_pi));


					player->set_cooldown();
					ammo_vector.push_back(round);


					animatedSprite3.setPosition((player->get_position().x) + (180 * (-cos(player->get_rotation_turret() / (180.0f / b2_pi)))), (player->get_position().y) + (180 * (-sin(player->get_rotation_turret() / (180.0f / b2_pi)))));
					animatedSprite3.setRotation(player->get_rotation_turret() - 90);
					animatedSprite3.play(*currentAnimation3);
				}


			}

			//----------------end of Main Gun------------------------------------------//

			if (player->get_health() <= 0 && player->get_has_animation_played() == false)
			{
				animatedSprite2.setPosition(player->get_position().x - 256, player->get_position().y - 256);
				animatedSprite2.play(*currentAnimation2);
				player->set_animation_has_played();
			}

			if ((player->get_distance_traveled().y - (level_move_count * 4096)) > (4096 - screen_height / 2))
			{
				int modulo_eka = 0;
				modulo_eka = (modulo_int % 2);

				if (modulo_eka == 0)
				{
					int modululo = 0;
					modululo = (level_move_count % 2);
					if (modululo == 0)
					{
						map3.setPosition(0, (level_move_count + 1) * 4096);
						map4.setPosition(0, (level_move_count + 1) * 4096);
					}
					else
					{
						map.setPosition(0, (level_move_count + 1) * 4096);
						map2.setPosition(0, (level_move_count + 1) * 4096);
					}
					level_move_count++;
				}
				else
				{
					modulo_int++;
				}

			}

			window->setView(*view);
			window->draw(map);
			window->draw(map3);
			o_manager.update(event, window, elapsed.asMilliseconds());
			o_manager.draw(window);

			//---DrawAmmo---//
			for (std::vector<Ammo*>::const_iterator iterator = ammo_vector.begin(), end = ammo_vector.end(); iterator != end; ++iterator)
			{
				(*iterator)->on_update(window);
				(*iterator)->on_draw(window);
			}
			//--------------//

			//---------reduce gun cooldown-----------------//
			if (player->get_cooldown() > 0)
			{
				player->reduce_cooldown(1);
			}

			//-------------------check contacts------------------------------------//
			std::vector<ContactCheck>::iterator pos;
			for (pos = ContactListener->_contacts.begin();
				pos != ContactListener->_contacts.end(); ++pos) {
				ContactCheck contact = *pos;

				if ((contact.fixtureA->GetBody()->GetUserData() == "ammo" && contact.fixtureB->GetBody()->GetUserData() == "player") ||
					(contact.fixtureA->GetBody()->GetUserData() == "player" && contact.fixtureB->GetBody()->GetUserData() == "ammo"))
				{
					player->reduce_health(1);
					animatedSprite.play(*currentAnimation);
					if (contact.fixtureA->GetBody()->GetUserData() == "ammo")
					{
						animatedSprite.setPosition(contact.fixtureA->GetBody()->GetPosition().x*SCALE, contact.fixtureA->GetBody()->GetPosition().y*SCALE);
					}
					if (contact.fixtureB->GetBody()->GetUserData() == "ammo")
					{
						animatedSprite.setPosition(contact.fixtureB->GetBody()->GetPosition().x*SCALE, contact.fixtureB->GetBody()->GetPosition().y*SCALE);
					}

				}
			}
			//--------------------------------------------------------------------------//

			//-----------------------Go through ammo and delete-----------------------------------------------//
			std::vector<Ammo*>::iterator it = ammo_vector.begin();
			while (it != ammo_vector.end())
			{
				if ((*it)->get_timer() <= 0)
				{
					myWorld.DestroyBody((*it)->get_ammo_body());
					it = ammo_vector.erase(it);
				}
				else
					it++;
			}

			//-----------------------------------------------------------------------//



			//----Animations----//
			animatedSprite.update(elapsed);
			animatedSprite2.update(elapsed);
			window->draw(animatedSprite);
			window->draw(animatedSprite2);
			//----Animations----//

			//---Draw_trees---//
			window->draw(map2);
			window->draw(map4);

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

				cooldown_sprite.setOrigin(sf::Vector2f(0, 20));
				cooldown_sprite.setPosition(screen_widht*0.14 + 200, screen_height*0.25);
				cooldown_sprite.setScale(sf::Vector2f(-0.025*player->get_cooldown(), 1));

				cooldown_sprite_back.setOrigin(sf::Vector2f(0, 20));
				cooldown_sprite_back.setPosition(screen_widht*0.14, screen_height*0.25);
				cooldown_sprite_back.setScale(sf::Vector2f(0.025 * 200, 1));


				text.setPosition(sf::Vector2f(screen_widht*0.2, (screen_height)*0.1));
				text2.setPosition(sf::Vector2f(screen_widht*0.1, (screen_height)*0.2));
				text3.setPosition(sf::Vector2f(screen_widht*0.14 + 300, (screen_height)*0.25));
				window->draw(text);
				window->draw(text2);
				if (player->get_cooldown() == 0)
				{
					window->draw(text3);
				}
				window->draw(player_healtbar__backround_sprite);
				window->draw(player_healtbar_sprite);
				window->draw(cooldown_sprite_back);
				window->draw(cooldown_sprite);

			}


			//---after_player_dies---//
			if (player->get_health() <= 0)
			{
				// Declare and load a font
				sf::Font font;
				font.loadFromFile("impact.ttf");
				// Create a text
				std::ostringstream score_text;
				score_text << "SCORE " << score;

				sf::Text text;
				text.setFont(font);
				text.setCharacterSize(140);
				text.setStyle(sf::Text::Bold);
				text.setColor(sf::Color::Yellow);
				text.setString(score_text.str());

				// Draw it
				window->setView(window->getDefaultView());
				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				text.setPosition(sf::Vector2f(screen_widht / 2, 150 + screen_height / 2));
				window->draw(game_over_sprite);
				window->draw(text);
			}
			//-----------------------//

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
	delete ContactListener;
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

	const int level2[] =
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

	map3.load("tileset_green_backround.png", sf::Vector2u(128, 128), level2, 32, 32);


	//Give me some trees...
	const int level_trees2[] =
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

	map4.load("tileset_trees.png", sf::Vector2u(256, 256), level_trees2, 16, 16);
}

void Game::set_view(sf::View *view, Player *player)
{
	//Alussa siirretään kamera pelaajaan.
	if ((view->getCenter().y < 2045.0f - (screen_height / 2)) && begin_of_game == 0)
	{
		view->setCenter(player->get_position());
		begin_of_game = 1;
	}


	view->setCenter(player->get_distance_traveled());


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