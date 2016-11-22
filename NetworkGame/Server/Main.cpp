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

#include "ServerGame.h"

namespace
{
	ENetAddress address;
	ENetHost * server;
	char message[1024];
	int playerCount = 0;
	std::vector<ENetPeer*> players;
	ENetPeer *newPeer;
}

void serverNetworkThread(ServerGame* game)
{
	ENetEvent event;
	/* Wait up to 1000 milliseconds for an event. */
	while (enet_host_service(server, &event, 10) > 0 || true)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			printf("A new client connected from %x:%u.\n",
				event.peer->address.host,
				event.peer->address.port);
			/* Store any relevant client information here. */
			event.peer->data = "Client information";

			newPeer = event.peer;
			players.push_back(newPeer);
			playerCount++;

			break;
		case ENET_EVENT_TYPE_RECEIVE:
			printf("A packet of length %u containing %08x was received from %s on channel %u.\n",
				event.packet->dataLength,
				*event.packet->data,
				event.peer->data,
				event.channelID);

			// Handle movement
			if (game->getRunning())
			{
				int dir = *event.packet->data;
				int intX = 0;
				int intY = 0;
				if (dir == 0)
				{
					intX = 1;
				}
				else if (dir == 1)
				{
					intX = -1;
				}
				else if (dir == 2)
				{
					intY = 1;
				}
				else if (dir == 3)
				{
					intY = -1;
				}

				game->networkUpdate(b2Vec2(float(intX*30), float(intY * 30)));
			}

			/* Clean up the packet now that we're done using it. */
			enet_packet_destroy(event.packet);

			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			printf("%s disconnected.\n", event.peer->data);
			/* Reset the peer's client information. */
			event.peer->data = NULL;
		}

		//---- Send player position packet to client
		if (playerCount > 0)
		{
			for (int i = 0; i < players.size(); i++)
			{
				int intMessage[2] = { 1 , 1 };
				int playerX = game->getPlayer()->getPos().x;
				int playerY = game->getPlayer()->getPos().y;
				intMessage[0] = playerX;
				intMessage[1] = playerY;
				ENetPacket *packet = enet_packet_create(intMessage, 8, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(players[i], 0, packet);
			}			
		}
	}

	atexit(enet_deinitialize);
}

int main()
{
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
