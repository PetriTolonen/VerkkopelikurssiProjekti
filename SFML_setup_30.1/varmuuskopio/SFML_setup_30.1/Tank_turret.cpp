#include "Tank_turret.h"


Tank_turret::Tank_turret(std::string n, int af, int al, int ari, int are, float rot, int am, float acc, float aimt)
{
	name = n;
	armor_front = af;
	armor_left = al;
	armor_rear = ari;
	armor_right = are;
	rotation_speed = rot;
	ammo_count = am;
	accuracy = acc;
	aim_time = aimt;
}

Tank_turret::Tank_turret()
{
	name = "panzer part";
	armor_front = 15;
	armor_left = 15;
	armor_rear = 15;
	armor_right = 15;
	rotation_speed = 1;

}

Tank_turret::~Tank_turret(void)
{


}


void Tank_turret::rotate(float angle)
{



}