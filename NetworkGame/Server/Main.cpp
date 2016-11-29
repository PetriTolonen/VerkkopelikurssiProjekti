#define _CRT_SECURE_NO_WARNINGS
#include<enet\enet.h>

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

// For threads
#include <list>
#include <mutex>
#include <thread>
#include <fstream>
#include <vector>
#include <string>
//
#include "ServerGame.h"

#include <SFML\System\Clock.hpp>

#include <math.h>

enum PacketTypes
{
	type_mData = 1,
	type_pData = 2,
	type_aData = 3
};

struct mData
{
	int id = type_mData;
	int dir = 0;
	int rot = 0;
};

struct pData
{
	int id = type_pData;
	int playerId = 0;
	float x = 0;
	float y = 0;
	float r = 0;
};

struct aData
{
	int id = type_aData;
	int connectionAlive = 0;
};

struct playerInfo
{
	ENetPeer *peer;
	bool connectionAlive = false;
	int number;
};

namespace
{
	ENetAddress address;
	ENetHost * server;
	char message[1024];
	int playerCount = 0;
	std::vector<playerInfo*> players;
	int receivePacketId;
	mData* in;
	float veloScale;
	float kickForce;
}

void serverNetworkThread(ServerGame* game)
{
	in = new mData();
	ENetEvent event;

	sf::Clock timeToCheckAlive;
	sf::Clock time;

	/* Wait up to 1000 milliseconds for an event. */
	while (enet_host_service(server, &event, 1) > 0 || true)
	{
		sf::Time elapsed = time.getElapsedTime();
		//---- Handle events
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			printf("A new client connected from %x:%u.\n",
				event.peer->address.host,
				event.peer->address.port);
			/* Store any relevant client information here. */
			event.peer->data = "Client information";

			if (playerCount < 2)
			{
				players[playerCount]->peer = event.peer;
				players[playerCount]->number = playerCount;
				playerCount++;
			}

			timeToCheckAlive.restart();

			break;
		case ENET_EVENT_TYPE_RECEIVE:
			//printf("A packet of length %u containing %08x was received from %s on channel %u.\n",
			//	event.packet->dataLength,
			//	*event.packet->data,
			//	event.peer->data,
			//	event.channelID);

			receivePacketId = (int)*event.packet->data;
			switch (receivePacketId)
			{
			case type_pData:
			{
				// For some reason
				printf("Wrong packet received \n");
				break;
			}
			case type_mData:
			{
				std::memcpy(in, &*event.packet->data, sizeof(mData));

				// Handle movement
				if (game->getRunning())
				{
					int intX = 0;
					int intY = 0;
					if (in->dir == 0)
					{
						intX = 1;
					}
					else if (in->dir == 1)
					{
						intX = -1;
					}
					else if (in->dir == 2)
					{
						intY = 1;
					}
					else if (in->dir == 3)
					{
						intY = -1;
					}

					veloScale = 0.25;
					kickForce = 0.002;

					if (event.peer->address.port == players[0]->peer->address.port)
					{
						game->networkUpdate(b2Vec2(float(intX * veloScale), float(intY * veloScale)), float(in->rot)*kickForce, 0);
					}
					else
					{
						game->networkUpdate(b2Vec2(float(intX * veloScale), float(intY * veloScale)), float(in->rot)*kickForce, 1);
					}

					break;
				}
			case type_aData:
			{
				for (int i = 0; i < playerCount; i++)
				{
					if (event.peer->address.port == players[i]->peer->address.port)
					{
						players[i]->connectionAlive = true;
					}
				}
				break;
			}
			default:
				break;
			}
			}

			/* Clean up the packet now that we're done using it. */
			enet_packet_destroy(event.packet);

			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			printf("%s disconnected.\n", event.peer->data);
			/* Reset the peer's client information. */
			event.peer->data = NULL;
		}

		//---- Send player position packets to client
		if (playerCount > 0 && elapsed.asMilliseconds() > 10)
		{
			//---- Send to all players
			for (int i = 0; i < playerCount; i++)
			{
				for (int x = 0; x < 3; x++)
				{
					pData send;
					send.x = game->getPlayer(x)->getPos().x;
					send.y = game->getPlayer(x)->getPos().y;
					send.r = game->getPlayer(x)->getRot();
					send.playerId = x;
					ENetPacket *packet = enet_packet_create(&send, sizeof(pData), ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(players[i]->peer, 0, packet);
				}
			}

			//---- Remove non alive players
			if (timeToCheckAlive.getElapsedTime().asSeconds() > 5)
			{
				for (int i = 0; i < playerCount; i++)
				{
					if (players[i]->connectionAlive == false)
					{
						playerCount--;
						printf("%08x players online.\n", playerCount);
					}
					else
					{
						players[i]->connectionAlive = false;
					}
				}

				timeToCheckAlive.restart();
			}
		}
	}

	atexit(enet_deinitialize);
}

int main()
{
	// Player slots
	playerInfo* player1 = new playerInfo();
	playerInfo* player2 = new playerInfo();
	players.push_back(player1);
	players.push_back(player2);

	ServerGame game;

	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}

	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	/* enet_address_set_host (& address, "x.x.x.x"); */
	address.host = ENET_HOST_ANY;
	/* Bind the server to port . */
	address.port = PORT;
	server = enet_host_create(&address /* the address to bind the server host to */,
		32      /* allow up to 32 clients and/or outgoing connections */,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}

	std::thread networkThread = std::thread(serverNetworkThread, &game);

	game.init();

	return 0;
}
