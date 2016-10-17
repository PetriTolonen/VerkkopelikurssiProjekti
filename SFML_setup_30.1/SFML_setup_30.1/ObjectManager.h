#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Object.h"
#include <list>
#include <cassert>

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager(void);

	void add_object(Object* const object);
	bool contains_object(const Object* const entity) const;
	void update(sf::Event event, sf::RenderWindow* win);
	void draw(sf::RenderWindow* win);
private:
	std::list<Object* const> objects;
	std::vector<Object* const> find_results;
	std::list<Object* const> destroyed_objects;

	

	void free_objects();

};
#endif
