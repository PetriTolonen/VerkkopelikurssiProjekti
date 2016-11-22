#include "Player.h"

Player::Player() : Object()
{
	
}

Player::~Player(void)
{

}

void Player::update(sf::Event event, sf::RenderWindow* win)
{

}

void Player::on_update(sf::Event event, sf::RenderWindow* win, float elapsed)
{
	
}

void Player::set_position(float x, float y)
{
	this->posX = x*30.0;
	this->posY = y*30.0;
}

float Player::rotate(float rotation_speed)
{
	return 0;

}

sf::Vector2f Player::get_position()
{
	return sf::Vector2f(posX, posY);
}

void Player::on_draw(sf::RenderWindow* win)
{

}

void Player::set_rotation(float rot)
{
	//rotation = rot;
}

void Player::set_animation_has_played()
{
	animation_has_played = true;
}

int Player::get_health()
{
	return 100;
}

bool Player::get_has_animation_played()
{
	return animation_has_played;
}