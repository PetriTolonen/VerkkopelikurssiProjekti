#ifndef WEAPON_H
#define WEAPON_H

#include "Tank_part.h"

class Weapon
{

public:

	Weapon();
	Weapon(std::string n, int cal, int dmg, int pen);
	~Weapon(void);

protected:

	std::string name;
	int calibre;
	int damage;
	int penetration;



};


#endif;