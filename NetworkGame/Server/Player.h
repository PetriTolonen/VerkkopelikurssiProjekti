#pragma once
#include "Box2D\Box2D.h"

class Player
{
public:
	Player(b2Body* player_body);
	~Player(void);

	void update();

	b2Vec2 getPos();
	float getRot();

	void handleBodyKick(float force, b2Body* ball);
	void handleBodyLinearVelocity(b2Vec2 velocity);

	b2Body* getBody();

	int getScore() { return score; };
	void scoreUp() { score++; };
	void zeroScore() { score = 0; };

private:
	b2Body* playerBody;
	float M_PI = 3.14159265358979323846;
	float turretDir;
	b2Vec2 pos;

	int score;
};