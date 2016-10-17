#include "Object.h"


Object::Object()
{
	enabled = true;
	destroyed = false;
}


Object::~Object()
{
}

void Object::set_texture(std::string texture_name)
{
	object_texture.loadFromFile(texture_name);
	sprite_name.setTexture(object_texture);
	sprite_name.setOrigin(object_texture.getSize().x / 2, object_texture.getSize().y / 2);
	object_texture.setSmooth(true);
	
}

sf::Vector2f Object::get_position()
{
	sf::Vector2f location;
	location = sprite_name.getPosition();
	return location;
}

float Object::get_rotation()
{	
	float rotation;
	rotation = sprite_name.getRotation();
	return rotation;
}

void Object::set_position(sf::Vector2f vector)
{
	sprite_name.setPosition(vector);
}

/*
void Object::set_rotation(float r)
{
	sprite_name.setRotation(r);
}
*/

void Object::set_position(float x, float y)
{
	sprite_name.setPosition(x, y);
}

bool Object::is_destroyed() const
{
	return destroyed;
}

void Object::destroy()
{
	destroyed = true;
}

void Object::update()
{
	if (!enabled || destroyed)
	{
		return;
	}
	on_update();
}

void Object::draw(sf::RenderWindow* win)
{
	if (!enabled || destroyed)
	{
		return;
	}
	on_draw(win);
}
