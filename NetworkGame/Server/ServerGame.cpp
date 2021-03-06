#include "ServerGame.h"

#include <sstream>

ServerGame::ServerGame() :myWorld(b2Vec2(0.0f, 10.0f))
{
}

void ServerGame::init()
{
	//---------Contact Listener-----------------//
	ContactListener = new MyContactListener();
	myWorld.SetContactListener(ContactListener);

	//----Scale
	SCALE = 40.f;
	
	//----Walls
	//createWall(myWorld, 1280, 32, 640, 16, SCALE);
	int w = 1280;
	int h = 32;
	int x = 640;
	int y = 16;
	b2BodyDef BodyDefWall;
	BodyDefWall.type = b2_staticBody;
	b2PolygonShape WallShape;

	b2Body* wallupper_body = myWorld.CreateBody(&BodyDefWall);

	WallShape.SetAsBox((w / 2) / SCALE, (h / 2) / SCALE);
	b2FixtureDef WallFixtureDef;
	WallFixtureDef.shape = &WallShape;
	WallFixtureDef.restitution = 0.2f;
	WallFixtureDef.friction = 0.5f;
	wallupper_body->SetUserData("wall");
	wallupper_body->CreateFixture(&WallFixtureDef);
	wallupper_body->SetTransform(b2Vec2(x / SCALE, y / SCALE), 0);

	//createWall(myWorld, 1280, 32, 640, 704, SCALE);
	w = 1280;
	h = 32;
	x = 640;
	y = 704;
	b2BodyDef BodyDefWall1;
	BodyDefWall1.type = b2_staticBody;
	b2PolygonShape WallShape1;

	b2Body* wallupper_body1 = myWorld.CreateBody(&BodyDefWall1);

	WallShape1.SetAsBox((w / 2) / SCALE, (h / 2) / SCALE);
	b2FixtureDef WallFixtureDef1;
	WallFixtureDef1.shape = &WallShape1;
	WallFixtureDef1.restitution = 0.2f;;
	WallFixtureDef1.friction = 0.5f;
	wallupper_body1->SetUserData("wall");
	wallupper_body1->CreateFixture(&WallFixtureDef1);
	wallupper_body1->SetTransform(b2Vec2(x / SCALE, y / SCALE), 0);

	//createWall(myWorld, 32, 720, 16, 360, SCALE);
	w = 32;
	h = 720;
	x = 14;
	y = 360;
	b2BodyDef BodyDefWall2;
	BodyDefWall2.type = b2_staticBody;
	b2PolygonShape WallShape2;

	b2Body* wallupper_body2 = myWorld.CreateBody(&BodyDefWall2);

	WallShape2.SetAsBox((w / 2) / SCALE, (h / 2) / SCALE);
	b2FixtureDef WallFixtureDef2;
	WallFixtureDef2.shape = &WallShape2;
	WallFixtureDef2.restitution = 0.2f;;
	WallFixtureDef2.friction = 0.5f;
	wallupper_body2->SetUserData("wall");
	wallupper_body2->CreateFixture(&WallFixtureDef2);
	wallupper_body2->SetTransform(b2Vec2(x / SCALE, y / SCALE), 0);

	//createWall(myWorld, 32, 720, 1264, 360, SCALE);
	w = 32;
	h = 720;
	x = 1266;
	y = 360;
	b2BodyDef BodyDefWall3;
	BodyDefWall3.type = b2_staticBody;
	b2PolygonShape WallShape3;

	b2Body* wallupper_body3 = myWorld.CreateBody(&BodyDefWall3);

	WallShape3.SetAsBox((w / 2) / SCALE, (h / 2) / SCALE);
	b2FixtureDef WallFixtureDef3;
	WallFixtureDef3.shape = &WallShape3;
	WallFixtureDef3.restitution = 0.2f;;
	WallFixtureDef3.friction = 0.5f;
	wallupper_body3->SetUserData("wall");
	wallupper_body3->CreateFixture(&WallFixtureDef3);
	wallupper_body3->SetTransform(b2Vec2(x / SCALE, y / SCALE), 0);
	//-----------------------------------------

	//createWall(myWorld, 32, 256, 20, 360, SCALE);
	w = 32;
	h = 256;
	x = 20;
	y = 360;
	b2BodyDef BodyDefGoal;
	BodyDefGoal.type = b2_staticBody;
	b2PolygonShape goalShape;

	b2Body* Goalupper_body = myWorld.CreateBody(&BodyDefGoal);

	goalShape.SetAsBox((w / 2) / SCALE, (h / 2) / SCALE);
	b2FixtureDef GoalFixtureDef;
	GoalFixtureDef.shape = &goalShape;
	GoalFixtureDef.restitution = 0.f;;
	GoalFixtureDef.friction = 1.f;
	Goalupper_body->SetUserData("goal");
	Goalupper_body->CreateFixture(&GoalFixtureDef);
	Goalupper_body->SetTransform(b2Vec2(x / SCALE, y / SCALE), 0);

	//----Tolpat
	float r = 10.0f;
	b2BodyDef BodyDefGoalTolppa;
	BodyDefGoalTolppa.type = b2_staticBody;
	b2CircleShape goalTolppa1Shape;

	b2Body* GoalTolppa1_body = myWorld.CreateBody(&BodyDefGoalTolppa);

	goalTolppa1Shape.m_radius = r / SCALE;
	b2FixtureDef GoalTolppaFixtureDef;
	GoalTolppaFixtureDef.shape = &goalTolppa1Shape;
	GoalTolppaFixtureDef.restitution = 0.f;;
	GoalTolppaFixtureDef.friction = 1.f;
	GoalTolppa1_body->SetUserData("goalTolppa");
	GoalTolppa1_body->CreateFixture(&GoalTolppaFixtureDef);
	GoalTolppa1_body->SetTransform(b2Vec2((x + w / 2) / SCALE, (y + h / 2) / SCALE), 0);

	//--
	b2Body* GoalTolppa2_body = myWorld.CreateBody(&BodyDefGoalTolppa);
	GoalTolppa2_body->SetUserData("goalTolppa");
	GoalTolppa2_body->CreateFixture(&GoalTolppaFixtureDef);
	GoalTolppa2_body->SetTransform(b2Vec2((x + w / 2) / SCALE, (y - h / 2) / SCALE), 0);

	//createWall(myWorld, 32, 256, 1260, 360, SCALE);
	w = 32;
	h = 256;
	x = 1260;
	y = 360;
	b2BodyDef BodyDefGoal1;
	BodyDefGoal1.type = b2_staticBody;
	b2PolygonShape goalShape1;

	b2Body* Goalupper_body1 = myWorld.CreateBody(&BodyDefGoal1);

	goalShape1.SetAsBox((w / 2) / SCALE, (h / 2) / SCALE);
	b2FixtureDef GoalFixtureDef1;
	GoalFixtureDef1.shape = &goalShape1;
	GoalFixtureDef1.restitution = 0.f;;
	GoalFixtureDef1.friction = 1.f;
	Goalupper_body1->SetUserData("goal");
	Goalupper_body1->CreateFixture(&GoalFixtureDef1);
	Goalupper_body1->SetTransform(b2Vec2(x / SCALE, y / SCALE), 0);

	//---Tolpat
	b2Body* GoalTolppa3_body = myWorld.CreateBody(&BodyDefGoalTolppa);
	GoalTolppa3_body->SetUserData("goalTolppa");
	GoalTolppa3_body->CreateFixture(&GoalTolppaFixtureDef);
	GoalTolppa3_body->SetTransform(b2Vec2((x - w / 2) / SCALE, (y + h / 2) / SCALE), 0);
	//--
	b2Body* GoalTolppa4_body = myWorld.CreateBody(&BodyDefGoalTolppa);
	GoalTolppa4_body->SetUserData("goalTolppa");
	GoalTolppa4_body->CreateFixture(&GoalTolppaFixtureDef);
	GoalTolppa4_body->SetTransform(b2Vec2((x - w / 2) / SCALE, (y - h / 2) / SCALE), 0);


	//-----------------------------------------

	float playerDamping = 10.0f;
	//---player_b2_body---//	
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody;
	BodyDef.fixedRotation = true;
	b2Body* player_body = myWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((20.f) / SCALE, (40.f) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 10.f;
	FixtureDef.friction = 0.2f;
	FixtureDef.restitution = 0.0f;
	FixtureDef.shape = &Shape;
	player_body->SetUserData("player");
	player_body->CreateFixture(&FixtureDef);
	player_body->SetTransform(b2Vec2(128 / SCALE, 360 / SCALE), 0);
	// movement dampening
	player_body->SetLinearDamping(playerDamping);
	//player_body->SetAngularDamping(0.1);
	//-----------------------------------------

	//---player_b2_body---//
	b2Body* player_body1 = myWorld.CreateBody(&BodyDef);

	player_body1->SetUserData("player1");
	player_body1->CreateFixture(&FixtureDef);
	player_body1->SetTransform(b2Vec2(1152 / SCALE, 360 / SCALE), 0);
	// movement dampening
	player_body1->SetLinearDamping(playerDamping);
	//player_body1->SetAngularDamping(0.1);
	//-----------------------------------------

	//---ball_b2_body---//	
	b2BodyDef BodyDefBall;
	BodyDefBall.type = b2_dynamicBody;
	b2Body* ball_body = myWorld.CreateBody(&BodyDefBall);

	b2CircleShape circleShape;
	circleShape.m_radius = 20.f / SCALE;
	b2FixtureDef FixtureDefCircle;
	FixtureDefCircle.density = 0.1f;
	FixtureDefCircle.friction = 0.01f;
	FixtureDefCircle.restitution = 0.5f;
	FixtureDefCircle.shape = &circleShape;
	ball_body->SetUserData("ball");
	ball_body->CreateFixture(&FixtureDefCircle);
	ball_body->SetTransform(b2Vec2(640 / SCALE, 360 / SCALE), 0);
	//ball_body->SetLinearDamping(0.0);
	ball_body->SetAngularDamping(0.005);
	//-----------------------------------------

	player = new Player(player_body);
	player1 = new Player(player_body1);
	ball = new Player(ball_body);
	players.push_back(player);
	players.push_back(player1);
	players.push_back(ball);
	ServerGameloop();
}

void ServerGame::resetGame()
{
	players[0]->getBody()->SetTransform(b2Vec2(128 / SCALE, 360 / SCALE), 0);
	players[0]->getBody()->SetLinearVelocity(b2Vec2(0, 0));
	players[1]->getBody()->SetTransform(b2Vec2(1152 / SCALE, 360 / SCALE), 0);
	players[1]->getBody()->SetLinearVelocity(b2Vec2(0, 0));
	players[2]->getBody()->SetTransform(b2Vec2(640 / SCALE, 360 / SCALE), 0);
	players[2]->getBody()->SetLinearVelocity(b2Vec2(0, 0));
}

//-----ServerGame_loop-----//
void ServerGame::ServerGameloop()
{
	gameTime.restart();

	while (true)
	{
		running = true;

		if (gameTime.getElapsedTime().asSeconds() >= 1.0f / 60.0f)
		{
			myWorld.Step(1.0f / 60.0f, 8, 4);

			for (size_t i = 0; i < players.size(); i++)
			{
				players[i]->getBody()->ApplyForceToCenter(players[i]->getBody()->GetMass() * -myWorld.GetGravity(), true);
				players[i]->update();
			}

			//-------------------check contacts------------------------------------//
			std::vector<ContactCheck>::iterator pos;
			for (pos = ContactListener->_contacts.begin();
				pos != ContactListener->_contacts.end(); ++pos) {
				ContactCheck contact = *pos;

				if ((contact.fixtureA->GetBody()->GetUserData() == "ball" && contact.fixtureB->GetBody()->GetUserData() == "goal") ||
					(contact.fixtureA->GetBody()->GetUserData() == "goal" && contact.fixtureB->GetBody()->GetUserData() == "ball"))
				{
					if (players[2]->getPos().x > 3) // ball x pos
					{
						players[0]->scoreUp();
						resetGame();
					}
					else
					{
						players[1]->scoreUp();
						resetGame();
					}
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

			gameTime.restart();
		}
		else //Sleep until next 1/60th of a second comes around
		{
			sf::Time sleepTime = sf::seconds((1.0f / 60.0f) - gameTime.getElapsedTime().asSeconds());
			sf::sleep(sleepTime);
		}
	}
	
	delete ContactListener;
}

void ServerGame::networkUpdate(b2Vec2 velocity, float force, int playerId)
{
	if (playerId == 1)
	{
		player->handleBodyLinearVelocity(velocity);
		player->handleBodyKick(force, ball->getBody());
	}
	else
	{
		player1->handleBodyLinearVelocity(velocity);
		player1->handleBodyKick(force, ball->getBody());
	}
}
