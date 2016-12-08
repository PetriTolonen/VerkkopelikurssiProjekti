#include "Tolppa.h"

Tolppa::Tolppa(std::string TolppaTextureName, float posX, float posY, float worldScale) : Object()
{
	this->posX = posX;
	this->posY = posY;
	this->worldScale = worldScale;
	set_texture(TolppaTextureName);

	get_sprite().setPosition(posX, posY);
}

Tolppa::~Tolppa(void)
{

}

void Tolppa::update(sf::Event event, sf::RenderWindow* win)
{

}

void Tolppa::on_update(sf::Event event, sf::RenderWindow* win, float elapsed)
{
}

void Tolppa::set_position(float x, float y)
{
	this->posX = x*worldScale;
	this->posY = y*worldScale;

	get_sprite().setPosition(posX, posY);
}

float Tolppa::rotate(float rotation_speed)
{
	return 0;

}

sf::Vector2f Tolppa::get_position()
{
	return sf::Vector2f(posX, posY);
}

void Tolppa::on_draw(sf::RenderWindow* win)
{
	win->draw(sprite_name);
}

void Tolppa::set_rotation(float rot)
{
	get_sprite().setRotation(rot);
}