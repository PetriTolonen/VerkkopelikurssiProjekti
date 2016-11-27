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

	void handleBodyAngularVelocity(float velAngular);
	void handleBodyLinearVelocity(b2Vec2 velocity);

private:
	b2Body* playerBody;
	float M_PI = 3.14159265358979323846;
	float turretDir;
	b2Vec2 pos;
};