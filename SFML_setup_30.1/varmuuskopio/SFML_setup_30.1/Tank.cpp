#include "Tank.h"

Tank::Tank()
{

}

Tank::~Tank(void)
{

}


void Tank::update()
{

}

void Tank::add_part()
{
	Tank_part *part = new Tank_part();
	tank_parts.push_back(part);

}
