#include "IncludeHelper.h"
#include <cmath>
#include <math.h>

//Classit

#include "TileMap.h"
#include "Game.h"
//#include "Tank_hull.h"
//Terveiset kotikoneelta. GitHub toimii.

#define M_PI 3.14159265358979323846 /* pi */

int main()
{
	Game a;
	a.run();
}

//
//{
//	//-----------------------------Tank Creation-----------------------------------------------//
//	//Tank_hull Tank_hull1();
//
//
//	//-----------------------------------------------------------------------------//
//
//
//
//	//--------------------------Screen_setup---------------------------------------//
//	sf::Vector2i screen_dimensions(1280, 720);
//	sf::RenderWindow window;
//	window.create(sf::VideoMode(screen_dimensions.x, screen_dimensions.y), "Tank Hunter Arcade");
//	window.setFramerateLimit(60);
//
//
//	//-------------------------------------------------------------//
//
//
//	//-----------------------------Something--------------------------------//
//	//window.setKeyRepeatEnabled(false);
//	//srand(time(0));
//	//---------------------------------------------------------------//
//
//	//--------------------View_options-------------------------------//
//
//	sf::View view;
//	view.reset(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
//	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
//	//----------------------------------------------------------------//
//
//
//	//----------------Tank_rotation_and_movement-----------------------------------------------------//
//	float rot_turret = 0;
//	float rot_hull = 0;
//	float turret_rot_speed = 1.2;
//	float hull_rot_speed = 0.8;
//
//	float o_clock = 1 / 60;
//
//	float hull_movement_acceleration = 0.2;
//	float hull_movement_speed_forwards = 0;
//	float hull_movement_speed_forwards_max = 2.1;
//
//	float hull_movement_speed_backwards = 0;
//	float hull_movement_speed_backwards_max = 0.7;
//
//	float speed = 5;
//	float angle = 60 * M_PI / 2;
//
//	float move_x = speed * cos(angle);
//	float move_y = speed * sin(angle);
//
//
//
//	//-----------------------------------------------------------------------------------------------//
//
//	//--------------------Tank----------------------------//
//	sf::Texture texture_tank_hull;
//	texture_tank_hull.loadFromFile("tank_hull_256.png");
//
//
//	sf::Texture texture_tank_turret;
//	texture_tank_turret.loadFromFile("tank_tower_256.png");
//
//
//	sf::Sprite sprite_tank_hull;
//	sprite_tank_hull.setTexture(texture_tank_hull);
//
//	sf::Sprite sprite_tank_turret;
//	sprite_tank_turret.setTexture(texture_tank_turret);
//
//	//Tank is now set to the beginning of the map
//	sprite_tank_hull.setPosition(2048, 2048 - (screen_dimensions.y / 2));
//	sprite_tank_hull.setOrigin(128, 128);
//
//	//Tank is now set to the beginning of the map
//	sprite_tank_turret.setPosition(2048, 2048 - (screen_dimensions.y / 2));
//	sprite_tank_turret.setOrigin(128, 128);
//
//	//Setting camera into the right position
//	view.setCenter(sprite_tank_hull.getPosition());
//
//	texture_tank_turret.setSmooth(true);
//	texture_tank_hull.setSmooth(true);
//
//
//
//	//-----------------------------------------------------------------------------------------------//
//
//	//Tilemap
//	//Backround
//	const int level[] =
//	{
//		0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//		0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
//		3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
//		0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3,
//		3, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
//		0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
//		3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
//		3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//		0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
//		0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0,
//		0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0,
//		3, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//		0, 3, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
//		0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
//		3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3,
//		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0,
//	};
//
//	TileMap map;
//	if (!map.load("tileset_green_backround.png", sf::Vector2u(128, 128), level, 32, 16))
//		return -1;
//	
//	//Give me some trees...
//	const int level2[] =
//	{
//		1, 2, 0, 3, 1, 1, 2, 0, 0, 1, 2, 2, 3, 1, 1, 1,
//		2, 1, 0, 3, 0, 0, 2, 0, 0, 1, 2, 0, 3, 1, 0, 1,
//		1, 1, 1, 1, 3, 3, 2, 0, 0, 3, 3, 3, 3, 2, 3, 1,
//		3, 1, 0, 1, 1, 0, 1, 0, 0, 1, 2, 3, 3, 1, 0, 1,
//		3, 2, 3, 3, 0, 0, 3, 0, 0, 3, 2, 3, 3, 3, 0, 1,
//		1, 3, 0, 1, 1, 1, 3, 0, 0, 2, 1, 0, 1, 1, 3, 1,
//		2, 2, 2, 3, 3, 0, 1, 0, 0, 2, 2, 1, 1, 1, 3, 1,
//		1, 1, 0, 3, 1, 0, 1, 0, 0, 1, 2, 0, 3, 1, 0, 1,
//	};
//
//	TileMap map2;
//	if (!map2.load("tileset_trees.png", sf::Vector2u(256, 256), level2, 16, 16))
//		return -1;
//
//
//	//------------------------------------Game_loop-------------------------------------------------//
//	while (window.isOpen())
//	{
//		sf::Clock clock;
//		sf::Time elapsed = clock.getElapsedTime();
//
//
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//			if (event.type == sf::Event::KeyPressed)
//			{
//				switch (event.key.code)
//				{
//				case sf::Keyboard::Escape:
//					window.close();
//					break;
//				}
//
//			}
//
//		}
//		//---------------------------------------------------------------------------------//
//
//
//		//----------------------------Controls-----------------------------------------//
//
//
//
//
//
//		//---------------------------------Turret--------------------------------------//
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//		{
//			sprite_tank_turret.rotate(-turret_rot_speed);
//
//		}
//
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//		{
//			sprite_tank_turret.rotate(turret_rot_speed);
//		}
//
//		//---------------------------------Hull--------------------------------------//
//
//
//		bool key_is_pressed = true;
//
//
//		while (key_is_pressed == true)
//		{
//			sf::Time t1 = sf::seconds(0.1f);
//			float _elapsed = t1.asSeconds();
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//			{
//				sprite_tank_turret.rotate(-hull_rot_speed);
//				sprite_tank_hull.rotate(-hull_rot_speed);
//			}
//
//
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//			{
//				sprite_tank_turret.rotate(hull_rot_speed);
//				sprite_tank_hull.rotate(hull_rot_speed);
//			}
//
//
//
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//			{
//
//
//				hull_movement_speed_forwards += _elapsed * hull_movement_acceleration;
//
//
//				if (hull_movement_speed_forwards > hull_movement_speed_forwards_max)
//				{
//					hull_movement_speed_forwards = hull_movement_speed_forwards_max;
//				}
//
//
//				//Tank hull moves now to the direction it faces.
//				sprite_tank_hull.move(sin(sprite_tank_hull.getRotation()*3.14159265 / 180) * hull_movement_speed_forwards, cos(sprite_tank_hull.getRotation()*3.14159265 / 180)*-hull_movement_speed_forwards);
//				sprite_tank_turret.setPosition(sprite_tank_hull.getPosition());
//				view.setCenter(sprite_tank_hull.getPosition());
//			}
//
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//			{
//
//
//				hull_movement_speed_backwards += _elapsed * hull_movement_acceleration;
//
//				if (hull_movement_speed_backwards > hull_movement_speed_backwards_max)
//				{
//					hull_movement_speed_backwards = hull_movement_speed_backwards_max;
//				}
//
//
//				//Tank hull moves now to the direction it faces.
//				sprite_tank_hull.move(sin(sprite_tank_hull.getRotation()*3.14159265 / 180) * -hull_movement_speed_backwards, cos(sprite_tank_hull.getRotation()*3.14159265 / 180)*hull_movement_speed_backwards);;
//				sprite_tank_turret.setPosition(sprite_tank_hull.getPosition());
//				view.setCenter(sprite_tank_hull.getPosition());
//			}
//
//			//_elapsed = 0;
//			//hull_movement_speed_forwards = 0;
//			//hull_movement_speed_backwards = 0;
//			
//			key_is_pressed = false;
//		
//		}
//			//----------------------------------------------------------End of Controls-----------------------------------------//
//
//			//shape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
//			
//			window.clear();
//			window.setView(view);
//			window.draw(map);
//			window.draw(sprite_tank_hull);
//			window.draw(sprite_tank_turret);
//			window.draw(map2);
//			window.display();
//		
//
//		
//	}
//	return 0;
//}
//
