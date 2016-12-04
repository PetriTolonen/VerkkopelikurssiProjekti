#ifndef GAME_H
#define GAME_H

#include "IncludeHelper.h"
#include "TileMap.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Player.h"
#include "ObjectManager.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "AnimatedSprite.h"

#include <iostream>

class Game
{
public:
	Game();
	void run();
	void gameloop(sf::RenderWindow *window, sf::View *view, MainMenu *main_menu);
	void level_creation();
	void networkUpdate(int id, float x, float y, float r);
	bool getRunning() { return running; };
	Player* getPlayer(int id) { return players[id]; };
	void setScore(int id, int score);

private:
	static const int screen_widht = 1280;
	static const int screen_height = 720;
	int level[1024];
	int level_trees[256];
	TileMap map;
	TileMap map2;

	static ObjectManager o_manager;

	int begin_of_game;

	static bool is_exiting();
	static void show_splash_screen(sf::RenderWindow *window);
	static void show_menu(sf::RenderWindow *window); //, MainMenu *main_menu);
	static void show_game_over(sf::RenderWindow *window);
	MainMenu main_menu;
	enum game_state {
		uninitialized,
		showing_splash,
		paused,
		showing_menu,
		playing,
		showing_game_over,
		exiting
	};
	static game_state _game_state;

	int time_passed_after_death;

	int level_move_count;
	int modulo_int;

	//----Init
	AnimatedSprite animatedSprite;
	Animation* currentAnimation;
	AnimatedSprite animatedSprite2;
	Animation* currentAnimation2;
	AnimatedSprite animatedSprite3;
	Animation* currentAnimation3;

	Player *player;
	Player *player1;
	Player *ball;
	std::vector<Player*> players;
	sf::Clock clock;
	float SCALE;

	bool running = false;

	sf::Font font;
};
#endif