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
	SCALE = 1.f;

	//---player_b2_body---//	
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody;
	b2Body* player_body = myWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((20.f) / SCALE, (20.f) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 10.f;
	FixtureDef.friction = 1.0f;
	FixtureDef.shape = &Shape;
	player_body->SetUserData("player");
	player_body->CreateFixture(&FixtureDef);
	player_body->SetTransform(b2Vec2(400, 500), 0);
	// movement dampening
	player_body->SetLinearDamping(10);
	player_body->SetAngularDamping(0);
	//-----------------------------------------

	//---player_b2_body---//
	b2Body* player_body1 = myWorld.CreateBody(&BodyDef);

	player_body1->SetUserData("player1");
	player_body1->CreateFixture(&FixtureDef);
	player_body1->SetTransform(b2Vec2(200, 300), 0);
	// movement dampening
	player_body1->SetLinearDamping(10);
	player_body1->SetAngularDamping(0);
	//-----------------------------------------

	//---ball_b2_body---//	
	b2Body* ball_body = myWorld.CreateBody(&BodyDef);

	b2CircleShape circleShape;
	b2FixtureDef FixtureDef;
	FixtureDef.density = 10.f;
	FixtureDef.friction = 1.0f;
	FixtureDef.shape = &circleShape;
	ball_body->SetUserData("player");
	ball_body->CreateFixture(&FixtureDef);
	ball_body->SetTransform(b2Vec2(400, 500), 0);
	// movement dampening
	ball_body->SetLinearDamping(10);
	ball_body->SetAngularDamping(0);
	//-----------------------------------------

	player = new Player(player_body);
	player1 = new Player(player_body1);
	players.push_back(player);
	players.push_back(player1);
	ServerGameloop();
}

//-----ServerGame_loop-----//
void ServerGame::ServerGameloop()
{
	while (true)
	{
		running = true;

		myWorld.Step(1.0f / 60.0f, 8, 4);

		for (size_t i = 0; i < players.size(); i++)
		{
			players[i]->update();
		}

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

void ServerGame::networkUpdate(b2Vec2 velocity, int playerId)
{
	if (playerId == 1)
	{
		player->handleBodyLinearVelocity(velocity);
	}
	else
	{
		player1->handleBodyLinearVelocity(velocity);
	}
}
