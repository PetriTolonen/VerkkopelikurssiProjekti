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
	float posX;
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
	while (enet_host_service(client, &event, 1000) > 0 || true)
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

			posX = *(int*)event.packet->data;
			
			/* Clean up the packet now that we're done using it. */
			enet_packet_destroy(event.packet);

			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			printf("%s disconnected.\n", event.peer->data);
			/* Reset the peer's client information. */
			event.peer->data = NULL;
		}

		// Network move
		if (game->getRunning())
		{
			game->networkUpdate(posX);
		}		

		int intMessage[1] = {1};
		printf("Say > ");		
		gets(message);

		intMessage[0] = std::stoi(message);

		char* buffer = (char*)intMessage;

		if (strlen(message) > 0) {
			ENetPacket *packet = enet_packet_create(buffer, 4, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
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
