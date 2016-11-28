#include "Player.h"

Player::Player(std::string playerTextureName, float posX, float posY, float speed, float worldScale) : Object()
{
	this->posX = posX;
	this->posY = posY;
	this->speed = speed;
	this->worldScale = worldScale;
	set_texture(playerTextureName);
}

Player::~Player(void)
{

}

void Player::update(sf::Event event, sf::RenderWindow* win)
{
	
}

void Player::on_update(sf::Event event, sf::RenderWindow* win, float elapsed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		networkMove.y = -1;
		moves = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		networkMove.y = 1;
		moves = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		networkMove.x = -1;
		moves = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		networkMove.x = 1;
		moves = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		networkRot = 1;
		moves = true;
	}
}

void Player::set_position(float x, float y)
{
	this->posX = x;//*worldScale;
	this->posY = y;//*worldScale;

	get_sprite().setPosition(posX, posY);
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
	win->draw(sprite_name);
}

void Player::set_rotation(float rot)
{
	get_sprite().setRotation(rot);
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

int Player::getNetworkMove()
{
	int dir = 9;
	if (networkMove.x >= 1)
	{
		dir = 0;
	}
	else if (networkMove.x <= -1)
	{
		dir = 1;
	}
	if (networkMove.y >= 1)
	{
		dir = 2;
	}
	else if (networkMove.y <= -1)
	{
		dir = 3;
	}
	zeroNetworkMove();
	return dir;
}

int Player::getNetworkRotate()
{
	int rot = networkRot;
	return rot;
}

void Player::zeroNetworkMove()
{
	networkMove = sf::Vector2i(0, 0); 
	networkRot = 0;
	moves = false;
}
