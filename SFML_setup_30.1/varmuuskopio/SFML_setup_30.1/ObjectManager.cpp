#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}

void ObjectManager::freeObjects() {
	std::for_each(destroyedObjects.begin(), destroyedObjects.end(), [this](Object* e) {
		objects.remove(e);

		delete e;
		e = nullptr;
	});

	destroyedObjects.clear();
}

void ObjectManager::addObject(Object* const object) {
	assert(object != nullptr && !object->is_destroyed());

	bool add = !containsObject(object);

	if (add) {
		objects.push_back(object);
	}
}

bool ObjectManager::containsObject(const Object* const entity) const 
{
	return std::find(objects.begin(), objects.end(), entity) != objects.end();
}

void ObjectManager::update()
{
	freeObjects();

	std::for_each(objects.begin(), objects.end(), [this](Object* e)
	{
		if (e->is_destroyed())
		{
			destroyedObjects.push_back(e);
			return;
		}
		e->update();
	});
}

void ObjectManager::draw()
{
	std::for_each(objects.begin(), objects.end(), [](Object* e)
	{
		delete e;
		e = nullptr;
	});
}