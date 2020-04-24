#include <bits/stdc++.h>

#include "MulticastSocket.h"

using namespace std;


int main(int argc, char const *argv[]) {
	string multicast;
	char msg[100];
	int port;
	long secs = 3, usecs = 0;

	if (argc != 3) {
		printf("[%s] [MULTICAST] [PORT]\n", argv[0]);
		exit(1);
	} 

	multicast = argv[1];
	port = atoi(argv[2]);
	MulticastSocket ms(port);
	ms.joinGroup(0, multicast);
	
	DatagramPacket packet(msg, sizeof(msg));
	cout << "Esperando solicitud... " << endl;
	ms.receiveTimeout(packet, secs, usecs);
	cout << packet;
	cout << "Mensaje: " << msg << endl;
	return 0;
}
