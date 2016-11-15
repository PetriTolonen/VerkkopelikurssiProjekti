#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "Player.h"
#include "Enemy.h"


class AiManager
{
public:
	AiManager();
	~AiManager(void);
	sf::Vector2f get_player_position(Player* player);

	void update(Player* player, Enemy* enemy);
	void move_to(sf::Vector2f player_position, Enemy* enemy);


private:
	
	b2Vec2 player_position;
	b2Vec2 enemy_position;
	std::vector<Enemy*> enemies;

};
#endif;