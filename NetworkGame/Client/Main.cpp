#include <enet\enet.h>

#include "IncludeHelper.h"
#include "Game.h"

// For threads
#include <list>
#include <mutex>
#include <thread>
#include <fstream>
#include <vector>

//
#include <stdio.h>
#include <string>

#define PORT 8888   //The port

namespace
{
	int posX;
	int posY;
	ENetAddress address;
	ENetHost *client;
	ENetPeer *peer;
	char message[1024];
	ENetEvent event;
	int eventStatus;
}

void netWorkThread(Game *game)
{
	posX = 0.0f;
	/* Wait up to 1000 milliseconds for an event. */
	while (enet_host_service(client, &event, 10) > 0 || true)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			printf("A new client connected from %x:%u.\n",
				event.peer->address.host,
				event.peer->address.port);
			/* Store any relevant client information here. */
			event.peer->data = "Client information";
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			printf("A packet of length %u containing %08x was received from %s on channel %u.\n",
				event.packet->dataLength,
				*event.packet->data,
				event.peer->data,
				event.channelID);

			if (game && game->getRunning())
			{
				int intMessageIn[2] = { 1 , 1 };
				std::memcpy(intMessageIn, &*event.packet->data, 8);
				posX = intMessageIn[0];
				posY = intMessageIn[1];
			}


			/* Clean up the packet now that we're done using it. */
			enet_packet_destroy(event.packet);

			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			printf("%s disconnected.\n", event.peer->data);
			/* Reset the peer's client information. */
			event.peer->data = NULL;
			break;
		}

		// Network move
		if (game && game->getRunning())
		{
			game->networkUpdate(posX, posY);

			int intMessage[1] = { 1 };
			//char* buffer = (char*)intMessage;

			if (game->getPlayer()->getMoves()) {
				intMessage[0] = game->getPlayer()->getNetworkMove();
				ENetPacket *packet = enet_packet_create(intMessage, 4, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
			}
		}
	}
}

int main()
{
	Game m_game;

	//---- Join server
	// a. Initialize enet
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occured while initializing ENet.\n");
		return EXIT_FAILURE;
	}

	atexit(enet_deinitialize);

	// b. Create a host using enet_host_create
	client = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);

	if (client == NULL) {
		fprintf(stderr, "An error occured while trying to create an ENet server host\n");
		exit(EXIT_FAILURE);
	}

	enet_address_set_host(&address, "localhost");
	address.port = PORT;

	// c. Connect and user service
	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) {
		fprintf(stderr, "No available peers for initializing an ENet connection");
		exit(EXIT_FAILURE);
	}

	eventStatus = 1;

	std::thread* networkThread = new std::thread(netWorkThread, &m_game);

	// Start Game
	m_game.run();
}
