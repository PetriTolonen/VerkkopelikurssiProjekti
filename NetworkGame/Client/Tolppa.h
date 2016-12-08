#ifndef TOLPPA_H
#define TOLPPA_H

#include "IncludeHelper.h"
#include "Object.h"

class Tolppa : public Object
{
public:
	Tolppa(std::string TolppaTextureName, float posX, float posY, float worldScale);
	~Tolppa(void);

	void on_update(sf::Event event, sf::RenderWindow* win, float elapsed);
	void update(sf::Event event, sf::RenderWindow* win);

	sf::Vector2f get_position();
	void on_draw(sf::RenderWindow* win);
	void set_position(float x, float y);
	float rotate(float rotation_speed);
	void set_rotation(float rot);

private:
	float posX;
	float posY;
	float worldScale;
};

#endif;
