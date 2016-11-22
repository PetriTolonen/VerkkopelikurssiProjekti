#include "Player.h"

Player::Player(b2Body* player_body)
{
	this->playerBody = player_body;
}

void Player::update()
{
	
}

b2Vec2 Player::getPos()
{
	return playerBody->GetPosition();;
}

void Player::handleBodyAngularVelocity(float velAngular)
{
	playerBody->SetAngularVelocity(velAngular);
}

void Player::handleBodyLinearVelocity(b2Vec2 velocity)
{
	playerBody->SetLinearVelocity(velocity);
}