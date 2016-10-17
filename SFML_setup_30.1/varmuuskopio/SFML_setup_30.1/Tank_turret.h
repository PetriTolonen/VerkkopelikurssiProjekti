#ifndef TANK_TURRET_H
#define TANK_TURRET_H

#include "Tank_part.h"

class Tank_turret :
	public Tank_part
{
public:

	Tank_turret();
	Tank_turret(std::string name, int af, int al, int ari, int are, float rot, int am, float acc, float aimt);
	~Tank_turret(void);

	void rotate(float angle);
	

protected:
	std::string name;
	int armor_front;
	int armor_left;
	int armor_right;
	int armor_rear;
	float rotation_speed;
	int ammo_count;
	float accuracy;
	float aim_time;




};
#endif;