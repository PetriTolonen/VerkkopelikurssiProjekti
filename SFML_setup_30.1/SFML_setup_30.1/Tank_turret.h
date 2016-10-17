#ifndef TANK_TURRET_H
#define TANK_TURRET_H

#include "Object.h"

class Tank_turret : public Object
{
public:

	Tank_turret();
	Tank_turret(std::string tank_turret_name,
		float rot, float ts, int cd);

	~Tank_turret(void);

	void rotate(float angle);
	void on_draw(sf::RenderWindow* win);
	void on_update();

	int get_cooldown();
	float get_traverse_speed();

protected:

	std::string texture_name;
	std::string tank_turret_name;
	float rotation_speed;
	float traverse_speed;
	int cooldown;



};
#endif;