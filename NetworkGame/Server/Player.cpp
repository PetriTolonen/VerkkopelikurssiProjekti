#include "Player.h"

Player::Player(b2Body* player_body)
{
	this->playerBody = player_body;
	score = 0;
}

void Player::update()
{
	
}

b2Vec2 Player::getPos()
{
	return playerBody->GetPosition();;
}

float Player::getRot()
{
	return playerBody->GetAngle();
}

void Player::handleBodyKick(float force, b2Body* ball)
{
	b2Vec2 dir = ball->GetWorldCenter() - playerBody->GetWorldCenter();
	float lenght = dir.Length();

	dir.Normalize();

	if (lenght < 1.8f)
	{
		dir.x = dir.x * force;
		dir.y = dir.y * force;
		ball->ApplyLinearImpulse(dir, ball->GetLocalCenter(), true);
	}
}

void Player::handleBodyLinearVelocity(b2Vec2 velocity)
{
	playerBody->ApplyLinearImpulse(velocity, playerBody->GetLocalCenter(), true);
}

b2Body * Player::getBody()
{
	return playerBody;
}
