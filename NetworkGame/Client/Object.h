#ifndef OBJECT_H
#define OBJECT_H

#include "IncludeHelper.h"


class Object
{
public:
	Object();
	virtual ~Object()=0;

	void set_texture(std::string texture_name);
	sf::Vector2f get_position();
	float get_rotation();
	void set_position(sf::Vector2f vector);
	void set_position(float x, float y);
	void set_rotation(float r);
	void rotate();//float r);
	bool is_destroyed() const;
	void destroy();
	void update(sf::Event event, sf::RenderWindow* win, float elapsed);
	void draw(sf::RenderWindow* win);
	sf::Sprite& get_sprite();
	

protected:

	sf::Vector2f position;
	float rotation;
	sf::Sprite sprite_name;
	sf::Texture object_texture;
	bool destroyed;
	bool enabled;

protected:
	virtual void on_update(sf::Event event, sf::RenderWindow* win, float elapsed);
	virtual void on_draw(sf::RenderWindow* win) = 0;
};
#endif
