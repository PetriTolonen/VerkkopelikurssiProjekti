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
#include <iostream>

#define PORT 8888   //The port

enum PacketTypes
{
	type_mData = 1,
	type_pData = 2,
	type_aData = 3
};

struct mData
{
	int id = type_mData;
	int dir;
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
	int receivePacketId;
	pData* in;

}

void netWorkThread(Game *game)
{
	in = new pData();
	posX = 0.0f;

	sf::Clock aliveSendTime;
	sf::Clock time;

	aliveSendTime.restart();

	/* Wait up to 1000 milliseconds for an event. */
	while (enet_host_service(client, &event, 1) > 0 || true)
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
			//printf("A packet of length %u containing %08x was received from %s on channel %u.\n",
			//	event.packet->dataLength,
			//	*event.packet->data,
			//	event.peer->data,
			//	event.channelID);

			if (game && game->getRunning())
			{
				receivePacketId = (int)*event.packet->data;
				switch (receivePacketId)
				{
				case type_pData:
				{
					std::memcpy(in, &*event.packet->data, sizeof(pData));

					game->networkUpdate(in->playerId, in->x, in->y, in->r);
					break;
				}				
				case type_mData:
				{
					// For some reason you got a move packet
					std::cout << "Wrong packet received" << std::endl;
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
			break;
		}

		// Network move
		if (game && game->getRunning())
		{
			mData send;
			if (game->getPlayer(0)->getMoves()) {
				send.rot = game->getPlayer(0)->getNetworkRotate();
				send.dir = game->getPlayer(0)->getNetworkMove();
				ENetPacket *packet = enet_packet_create(&send, sizeof(mData), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
			}
		}

		// Im alive
		if (aliveSendTime.getElapsedTime().asSeconds() > 2)
		{
			aData send;
			send.connectionAlive = 1;
			ENetPacket *packet = enet_packet_create(&send, sizeof(aData), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			aliveSendTime.restart();
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

	char iostreamaddress[20];

	std::cout<<"Give server IP address" << std::endl;
	std::cin.getline(iostreamaddress, 20);

	enet_address_set_host(&address, iostreamaddress);
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
