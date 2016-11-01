#ifndef AMMO_H
#define AMMO_H

#include "IncludeHelper.h"
#include "Object.h"
#include <iostream>
#include "Box2D\Box2D.h"

class Ammo : public Object
{
public:

	Ammo(std::string n, b2Body* ammo_body, float velo, int dmg, int pen, float x, float y);
	Ammo();
	~Ammo();

	void on_update(sf::RenderWindow* win);

	int get_damage();
	int get_penetration();

	void on_draw(sf::RenderWindow* win);

	b2Vec2 get_position();
	void set_position(float x, float y);
	float get_velocity();
	b2Body* get_ammo_body();
	void start_contact();
	void end_contact();
	void set_velocity(float x, float y);
	void set_coord(float _x, float _y);
	void set_rotation(float rot);
	int get_timer();

protected:
	b2Body* ammo_body;
	std::string texture_name;
	float velocity;
	int damage;
	int penetration;
	float x;
	float y;
	float radians;
	bool is_hit;
	int timer;

	

	
};
#endif