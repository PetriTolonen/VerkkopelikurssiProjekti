#ifndef GAME_H
#define GAME_H

#include "IncludeHelper.h"
#include "TileMap.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Ammo.h"
#include "Enemy.h"
#include "AiManager.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameOver.h"

#include "Box2D\Box2D.h"
#include "ContactChecker.h"
#include "AnimatedSprite.h"

class Game
{
public:
	Game();
	void run();
	void gameloop(sf::RenderWindow *window, sf::View *view, MainMenu *main_menu);
	void level_creation();
	void set_view(sf::View *view, Player *player);

private:
	static const int screen_widht = 1920;
	static const int screen_height = 1080;
	int level[1024];
	int level_trees[256];
	TileMap map;
	TileMap map2;
	TileMap map3;
	TileMap map4;

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
	std::vector<Ammo*> ammo_vector;

	MyContactListener *ContactListener;

	int time_passed_after_death;
	int score;

	int level_move_count;
	int modulo_int;

	//----Init
	b2World myWorld;

	sf::Texture boxTexture;
	sf::Texture deathImage;
	sf::Texture cooldown_texture;
	sf::Sprite cooldown_sprite;
	sf::Texture cooldown_texture_back;
	sf::Sprite cooldown_sprite_back;
	sf::Texture player_healtbar_texture;
	sf::Sprite player_healtbar_sprite;
	sf::Texture player_healtbar_texture_backround;
	sf::Sprite player_healtbar__backround_sprite;

	sf::Sprite game_over_sprite;

	AnimatedSprite animatedSprite;
	Animation* currentAnimation;
	AnimatedSprite animatedSprite2;
	Animation* currentAnimation2;
	AnimatedSprite animatedSprite3;
	Animation* currentAnimation3;

	AiManager *ai_manager;

	Player *player;
	sf::Clock clock;
	float SCALE;
};
#endif