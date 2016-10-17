#include "Tank_turret.h"


Tank_turret::Tank_turret(std::string tank_turret_name, float rot, float ts, int cd) : Object()
{

	texture_name = tank_turret_name + "_256.png";
	set_texture(texture_name);
	object_texture.setSmooth(true);
	rotation_speed = rot;
	traverse_speed = ts;
	cooldown = cd;
}

Tank_turret::Tank_turret() : Object()
{
	texture_name = "tank_tower_256.png";
	set_texture(texture_name);
	rotation_speed = 1;
	cooldown = 2;
}

Tank_turret::~Tank_turret(void)
{


}


void Tank_turret::rotate(float angle)
{



}

void Tank_turret::on_draw(sf::RenderWindow* win)
{
	win->draw(sprite_name);
}

void Tank_turret::on_update()
{

}

float Tank_turret::get_traverse_speed()
{
	return traverse_speed;
}

int Tank_turret::get_cooldown()
{
	return cooldown;
}