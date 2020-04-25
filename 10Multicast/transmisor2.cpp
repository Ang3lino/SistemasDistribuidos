
#include <bits/stdc++.h>

#include "MulticastSocket.h"

using namespace std;


void parse_args(int argc, char *argv[], string &multicast, int &port, int &ttl, int *msg) {
	if (argc != 6) {
        printf("[%s] [MULTICAST] [PORT] [TTL] [int] [int]\n\n", argv[0]);
		exit(1);
	} 
    
	multicast = argv[1];
	port = atoi(argv[2]);
	ttl = atoi(argv[3]);
	msg[0] = atoi(argv[4]);
	msg[1] = atoi(argv[5]);
}


int main(int argc, char *argv[]) {
    string multicast;
    int msg[2];
    int port, ttl = 3;
    parse_args(argc, argv, multicast, port, ttl, msg);   

    MulticastSocket msock;
    DatagramPacket pack((char *) msg, 2 * sizeof(int), multicast, port);
    msock.send(pack, ttl);

    for (int i = 0; i < 3; ++i) {
        cout << "Reciviendo suma \n";
        int result;
        DatagramPacket pack2((char *) &result, sizeof(int));
        msock.receiveTimeout(pack2, 3, 0);
        printf("%d \n", result);
    }

    return 0;
}
