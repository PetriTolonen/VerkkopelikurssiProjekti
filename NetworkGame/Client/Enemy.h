#ifndef ENEMY_H
#define ENEMY_H

#include "IncludeHelper.h"
#include "Object.h"
#include "Box2D\Box2D.h"
#include "Ammo.h"
#include "Tank_hull.h"
#include "Tank_turret.h"


class Enemy : public Object
{
public:
	Enemy(b2Body* enemy_body, Tank_hull* t, Tank_turret* tt, float msf, float msb, float maf, float mab, float mmsf, float mmsb, float m, int mcd);
	~Enemy(void);
	void on_update(sf::Event event, sf::RenderWindow* win);
	void update(sf::Event event, sf::RenderWindow* win);
	void on_draw(sf::RenderWindow* win);
	void reduce_health(int amount);

	void set_position(float x, float y);
	
	

	float get_rotation();
	float get_rotation_turret();
	int get_cooldown();
	
	sf::Vector2f get_position();
	bool get_can_fire();
	void set_cooldown();
	void reduce_cooldown(int amount);
	b2Body* get_body();
	void move_to(sf::Vector2f player_position, float player_rotation);
	int get_health();
	bool get_has_animation_played();
	void set_animation_has_played();
	void set_can_fire_false();
	bool get_has_score_given();
	void set_score_given_false();
	void set_score_given_true();

	void set_body_position(float x, float y);

private:
	bool at_destination;
	int health;
	b2Body* enemy_body;
	Tank_turret* t_turret;
	Tank_hull* t_hull;
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
	sf::Vector2f distance_traveled;

	bool animation_played;
	float random_x;
	float random_y;
	float rng_decider;
	float timer;
	bool score_given;
};
#endif;