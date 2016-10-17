#ifndef GAME_H
#define GAME_H

#include "IncludeHelper.h"
#include "TileMap.h"
#include "ObjectManager.h"
#include "Object.h"
//#include "Tank_hull.h"

class Game
{
public:
	void run();
	void update();
	void gameloop(sf::RenderWindow *window, sf::View *view);
	void level_creation();

private:
	static const int screen_widht = 1280;
	static const int screen_height = 720;
	int level[512];
	int level_trees[256];
	TileMap map;
	TileMap map2;
};
#endif