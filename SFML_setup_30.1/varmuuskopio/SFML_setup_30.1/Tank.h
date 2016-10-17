#ifndef TANK_H
#define TANK_H

#include "Tank_hull.h"
#include "Tank_turret.h"
#include "Weapon.h"
#include "Tank_part.h"
#include "Object.h"


class Tank :
	public Object
{

public:
	Tank();
	~Tank(void);
	void update();
	void add_part();
	void remove_part();


protected:
	std::vector<Tank_part*> tank_parts;
	
};
#endif;