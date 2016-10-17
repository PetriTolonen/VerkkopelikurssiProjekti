#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"
#include "IncludeHelper.h"

class Player
{
public:
	Player(Tank_hull* t, float rop, float m_pi, float ang, float msf, float msb, float maf, float mab, float mmsf);
	~Player(void);
	void update();
	void reduce_health(int amount);
	void increase_health(int amount);
	void set_health();

	sf::Vector2f get_position();
	void on_draw(sf::RenderWindow* win);
	float get_position_x();
	float get_position_y();
	void set_position(float x, float y);
	float rotate(float rotation_speed);
	void set_rotation(float rot);

private:
	int health;
	//sf::Sprite player_sprite_hull;
	Tank_hull* t;
	float x;
	float y;
	float rotation_speed;
	float rotation;
	//----------Clock-----------------//
	sf::Time t1 = sf::seconds(0.1f);
	float _elapsed = t1.asSeconds();


	//---------Tank_hull_statistics------//
	Tank_hull tank_hull;
	float M_PI = 3.14159265358979323846;
	float angle = 60 * M_PI / 2;
	float momentary_speed_forward = 0;
	float momentary_speed_backward = 0;
	float momentary_acceleration_forward = 0;
	float momentary_acceleration_backward = 0;
	float momentary_max_speed_forward = 0;
	//std::string tank_name;

	/*
	float momentary_acceleration_forward = tank_hull.get_acceleration_forward();
	float momentary_max_speed_forward = tank_hull.get_max_speed_forward();
	*/


};




#endif;