
#include <bits/stdc++.h>

#include "MulticastSocket.h"

using namespace std;


int main(int argc, char *argv[]) {
    string multicast;
    char msg[100];
    int port, ttl;
    
	if (argc != 5) {
        printf("[%s] [MULTICAST] [PORT] [TTL] [MESSAGE]\n\n", argv[0]);
		exit(1);
	} 
    
	multicast = argv[1];
	port = atoi(argv[2]);
	ttl = atoi(argv[3]);
    strcpy(msg, argv[4]);

    MulticastSocket msock;
    DatagramPacket packet(msg, strlen(msg) + 1, multicast, port);
    msock.send(packet, ttl);
    return 0;
}
