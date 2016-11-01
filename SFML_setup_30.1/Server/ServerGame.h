#pragma once

#define MP_I = 3.14159265358979323846
#define M_HP = 745.699872
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#include "ObjectManager.h"
#include "Object.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Ammo.h"

#include "Box2D.h"
#include "ContactChecker.h"

class ServerGame
{
public:
	ServerGame();
	void run();
	void ServerGameloop();
	void level_creation();

private:
	static const int screen_widht = 1920;
	static const int screen_height = 1080;
	int level[1024];
	int level_trees[256];

	static ObjectManager o_manager;

	int begin_of_ServerGame;

	static bool is_exiting();
	
	enum ServerGame_state {
		paused,
		playing,
		exiting
	};
	static ServerGame_state _ServerGame_state;
	std::vector<Ammo*> ammo_vector;

	MyContactListener *ContactListener;

	int time_passed_after_death;
	int score;

	int level_move_count;
	int modulo_int;

	//----Init
	b2World myWorld;

	Player *player;

	sf::Clock clock;
	float SCALE;
};