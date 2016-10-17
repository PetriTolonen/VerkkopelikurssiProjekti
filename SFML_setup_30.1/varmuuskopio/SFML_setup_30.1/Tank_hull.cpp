#include "Tank_hull.h"

Tank_hull::Tank_hull(std::string tank_hull_name, float acf, float acb, float trs, float msf, float msb)
{
	texture_name = tank_hull_name + "_256.png";
	
	set_texture(texture_name);
	object_texture.setSmooth(true);
	acceleration_forward = acf;
	acceleration_backward = acb;
	traverse_speed = trs;
	max_speed_forward = msf;
	max_speed_backward = msb;
}

Tank_hull::Tank_hull()
{
	
	set_texture(texture_name);
	acceleration_forward = 0.5;
	acceleration_backward = 0.2;
	traverse_speed = 2.0;
	max_speed_forward = 4.0;
	max_speed_backward = 2.0;

}

Tank_hull::~Tank_hull(void)
{
}

void Tank_hull::on_update()
{

}

void Tank_hull::on_draw(sf::RenderWindow* win)
{
	win->draw(sprite_name);//hull_sprite_name);
}


float Tank_hull::get_acceleration_backward()
{
	return acceleration_backward;
}

float Tank_hull::get_acceleration_forward()
{
	return acceleration_forward;
}

float Tank_hull::get_traverse_speed()
{
	return traverse_speed;
}

float Tank_hull::get_max_speed_forward()
{
	return max_speed_forward;
}

float Tank_hull::get_max_speed_backward()
{
	return max_speed_backward;
}

std::string Tank_hull::get_hull_tank_name()
{
	return tank_hull_name;
}

sf::Sprite&Tank_hull::get_sprite()
{
	return hull_sprite_name;
}