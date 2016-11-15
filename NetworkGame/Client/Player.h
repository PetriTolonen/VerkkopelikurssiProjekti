#ifndef PLAYER_H
#define PLAYER_H

#include "IncludeHelper.h"
#include "Object.h"
#include "Box2D\Box2D.h"
#include "Ammo.h"
#include "Tank_hull.h"
#include "Tank_turret.h"

class Player : public Object
{
public:
	Player(b2Body* player_body, Tank_hull* t, Tank_turret* tt, float msf, float msb, float maf, float mab, float mmsf, float mmsb, float m, int mcd);
	~Player(void);

	void on_update(sf::Event event, sf::RenderWindow* win);
	void update(sf::Event event, sf::RenderWindow* win);
	
	void reduce_health(int amount);
	void increase_health(int amount);
	void set_health();

	b2Body* get_body();
	float get_rotation();
	float get_rotation_turret();

	int get_cooldown();

	sf::Vector2f get_position();
	void on_draw(sf::RenderWindow* win);
	void set_body_position(float x, float y);
	void set_position(float x, float y);
	float rotate(float rotation_speed);
	void set_rotation(float rot);
	void set_weight(float weight_hull);
	

	sf::Vector2f get_distance_traveled();
	bool get_can_fire();
	void set_cooldown();
	void reduce_cooldown(int amount);

	void set_animation_has_played();
	int get_health();
	bool get_has_animation_played();

private:
	
	int health;
	b2Body* player_body;
	Tank_turret* tt;
	Tank_hull* t;
	float x;
	float y;
	float turret_rotation_speed;
	float hull_rotation_speed;
	//----------Clock-----------------//
	sf::Time t1 = sf::seconds(0.1f);
	float _elapsed = t1.asSeconds();
	//-----------Main Gun---------------------//
	int momentary_cooldown = 0;
	bool can_fire = true;
	

	//---------Tank_hull_statistics------//
	Tank_hull tank_hull;
	float M_PI = 3.14159265358979323846;
	float angle = 60 * M_PI / 2;
	float momentary_speed_forward = 0;
	float momentary_speed_backward = 0;
	float momentary_acceleration_forward = 0;
	float momentary_acceleration_backward = 0;
	float momentary_max_speed_forward = 0;
	float momentary_max_speed_backward = 0;
	float momentum = 0;
	float weight = 0;

	//------------------------------------//
	bool is_moving_forward = false;
	bool is_moving_backward = false;

	bool forward_is_pressed = false;
	bool backward_is_pressed = false;

	sf::Vector2f distance_traveled;

	bool animation_has_played;
};




#endif;