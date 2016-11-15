#pragma once
#include "Box2D\Box2D.h"

class Player
{
public:
	Player(b2Body* player_body);
	~Player(void);

	void update();

	void rotateAim(float rotation);
	void handleBodyAngularVelocity(float velAngular);
	void handleBodyLinearVelocity(float velX, float velY);

private:
	b2Body* playerBody;
	float M_PI = 3.14159265358979323846;
	float turretDir;
};