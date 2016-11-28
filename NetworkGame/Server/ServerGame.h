#pragma once

#define MP_I = 3.14159265358979323846
#define M_HP = 745.699872
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f


#include "Player.h"
#include "Box2D\Box2D.h"
#include "ContactChecker.h"

class ServerGame
{
public:
	ServerGame();
	void init();
	void ServerGameloop();
	void networkUpdate(b2Vec2 velocity, float angVel, int playerId);
	bool getRunning() { return running; };
	Player* getPlayer(int id) { return players[id]; };

private:
	static const int screen_widht = 1280;
	static const int screen_height = 720;
	int level[1024];
	int level_trees[256];
	
	enum ServerGame_state {
		paused,
		playing,
		exiting
	};
	static ServerGame_state _ServerGame_state;
	//std::vector<Ammo*> ammo_vector;

	MyContactListener *ContactListener;

	//----Init
	b2World myWorld;

	Player *player;
	Player *player1;
	Player *ball;
	std::vector<Player*> players;

	float SCALE;
	bool running = false;
};