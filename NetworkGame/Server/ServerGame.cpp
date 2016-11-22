#include "ServerGame.h"

#include <sstream>

ServerGame::ServerGame() :myWorld(b2Vec2(0.0f, 0.0f))
{
}

void ServerGame::init()
{
	//---------Contact Listener-----------------//
	ContactListener = new MyContactListener();
	myWorld.SetContactListener(ContactListener);

	//----Scale
	SCALE = 30.f;

	//---player_b2_body---//	
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody;
	b2Body* player_body = myWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((31.f) / SCALE, (66.f) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 10.f;
	FixtureDef.friction = 1.0f;
	FixtureDef.shape = &Shape;
	player_body->SetUserData("player");
	player_body->CreateFixture(&FixtureDef);
	player_body->SetTransform(b2Vec2(18.0 / SCALE, (screen_height / 2) / SCALE), 0);
	// movement dampening
	player_body->SetLinearDamping(10);
	player_body->SetAngularDamping(0);
	//---player_b2_body---//

	player = new Player(player_body);
	ServerGameloop();
}

//-----ServerGame_loop-----//
void ServerGame::ServerGameloop()
{
	while (true)
	{
		running = true;

		myWorld.Step(1.0f / 60.0f, 8, 4);

		player->update();

		//-------------------check contacts------------------------------------//
		std::vector<ContactCheck>::iterator pos;
		for (pos = ContactListener->_contacts.begin();
			pos != ContactListener->_contacts.end(); ++pos) {
			ContactCheck contact = *pos;

			if ((contact.fixtureA->GetBody()->GetUserData() == "ammo" && contact.fixtureB->GetBody()->GetUserData() == "player") ||
				(contact.fixtureA->GetBody()->GetUserData() == "player" && contact.fixtureB->GetBody()->GetUserData() == "ammo"))
			{
				//player->reduce_health(1);
			}
		}
		//--------------------------------------------------------------------------//

		//-----------------------Go through ammo and delete-----------------------------------------------//
		/*std::vector<Ammo*>::iterator it = ammo_vector.begin();
		while (it != ammo_vector.end())
		{
		if ((*it)->get_timer() <= 0)
		{
		myWorld.DestroyBody((*it)->get_ammo_body());
		it = ammo_vector.erase(it);
		}
		else
		it++;
		}*/

		//-----------------------------------------------------------------------//
	}
	
	delete ContactListener;
}

void ServerGame::networkUpdate(b2Vec2 velocity)
{
	player->handleBodyLinearVelocity(velocity);
}
