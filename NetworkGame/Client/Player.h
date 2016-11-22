#ifndef PLAYER_H
#define PLAYER_H

#include "IncludeHelper.h"
#include "Object.h"

class Player : public Object
{
public:
	Player(std::string playerTextureName, float posX, float posY, float speed, float worldScale);
	~Player(void);

	void on_update(sf::Event event, sf::RenderWindow* win, float elapsed);
	void update(sf::Event event, sf::RenderWindow* win);

	sf::Vector2f get_position();
	void on_draw(sf::RenderWindow* win);
	void set_position(float x, float y);
	float rotate(float rotation_speed);
	void set_rotation(float rot);

	void set_animation_has_played();
	int get_health();
	bool get_has_animation_played();

private:
	float posX;
	float posY;
	float worldScale;
	float speed;
	bool animation_has_played;
};

#endif;