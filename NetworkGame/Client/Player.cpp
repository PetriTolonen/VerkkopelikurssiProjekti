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
		posY -= speed * elapsed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		posY += speed * elapsed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		posX -= speed * elapsed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		posX += speed * elapsed;
	}

	set_position(posX, posY);
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