#ifndef OBJECT_H
#define OBJECT_H

#include "IncludeHelper.h"

class Object
{
public:
	Object();
	~Object();

	void set_texture(std::string texture_name);
	sf::Vector2f get_position();
	float get_rotation();
	void set_position(sf::Vector2f vector);
	void set_position(float x, float y);
	void set_rotation(float r);
	void rotate();//float r);
	bool is_destroyed() const;
	void destroy();
	void update();
	void draw(sf::RenderWindow* win);
	

protected:

	sf::Vector2f position;
	float rotation;
	sf::Sprite sprite_name;
	sf::Texture object_texture;
	bool destroyed;
	bool enabled;

protected:
	virtual void on_update() = 0;
	virtual void on_draw(sf::RenderWindow* win) = 0;
};
#endif
