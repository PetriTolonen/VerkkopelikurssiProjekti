#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Object.h"
#include <list>
#include <cassert>

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void addObject(Object* const object);
	bool containsObject(const Object* const entity) const;
	void update();
	void draw();
private:
	std::list<Object* const> objects;
	std::vector<Object* const> findResults;
	std::list<Object* const> destroyedObjects;

	void freeObjects();
};
#endif
