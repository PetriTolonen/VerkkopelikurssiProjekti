#ifndef WORLD_H
#define WORLD_H

#include "IncludeHelper.h"

class World
{
public:
	World();
	~World();

	void update();
	void draw(sf::RenderWindow *window, sf::View * view);


};
#endif
