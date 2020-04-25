#include <bits/stdc++.h>

#include "MulticastSocket.h"

using namespace std;


void parse_args(int argc, char const *argv[], string &multicast, int &port) {
	if (argc != 3) {
		printf("[%s] [MULTICAST] [PORT]\n", argv[0]);
		exit(1);
	} 
	multicast = argv[1];
	port = atoi(argv[2]);
}

int main(int argc, char const *argv[]) {
	string multicast;
	int msg[2];
	int port, ttl = 3;
	long secs = 3, usecs = 0;
	parse_args(argc, argv, multicast, port);

	MulticastSocket msock(port);
	DatagramPacket packet((char *) msg, sizeof(msg));
	msock.joinGroup(0, multicast);

	cout << "Esperando solicitud... " << endl;
	msock.receiveTimeout(packet, secs, usecs);
	cout << packet;

	int sum = msg[0] + msg[1];
	printf("%d + %d = %d", msg[0], msg[1], sum);
	DatagramPacket packet2((char *) &sum, sizeof(int), packet.getAddress(), packet.getPort());
    msock.send(packet2, ttl);

	cout << endl;
	return 0;
}
