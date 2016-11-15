#include "Player.h"

Player::Player(b2Body* player_body)
{
	this->playerBody = player_body;
}

void Player::update()
{

}

void Player::rotateAim(float rotation)
{
	turretDir = rotation;
}

void Player::handleBodyAngularVelocity(float velAngular)
{
	playerBody->SetAngularVelocity(velAngular);
}

void Player::handleBodyLinearVelocity(float velX, float velY)
{
	playerBody->SetLinearVelocity(b2Vec2(velX, velY));
}