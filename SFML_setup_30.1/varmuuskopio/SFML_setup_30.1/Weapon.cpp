#include "Weapon.h"


Weapon::Weapon(std::string n, int cal, int dmg, int pen)
{
	name = n;
	calibre = cal;
	damage = dmg;
	penetration = pen;


}

Weapon::Weapon()
{
	name = "KwK37mm";
	calibre = 37;
	damage = 5;
	penetration = 25;

}


Weapon::~Weapon(void)
{


}