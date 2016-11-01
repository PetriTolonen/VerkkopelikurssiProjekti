#include "Box2D\Box2D.h"
#include <vector>
#include <algorithm>
#include "Ammo.h"

struct ContactCheck {
	b2Fixture *fixtureA;
	b2Fixture *fixtureB;
	bool operator==(const ContactCheck& other) const
	{
		return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
	}
};

class MyContactListener : public b2ContactListener {

public:
	std::vector<ContactCheck>_contacts;

	MyContactListener();
	~MyContactListener();

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

};