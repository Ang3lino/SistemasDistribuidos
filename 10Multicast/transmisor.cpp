
#include <bits/stdc++.h>

#include "MulticastSocket.h"

using namespace std;


int main(int argc, char *argv[]) {
    string ipmulti;
    char str[100];
    int port, ttl;
    string buff;
    
	if (argc != 5) {
        printf("[%s] [MULTICAST] [PORT] [TTL] [MESSAGE]\n\n", argv[0]);
		exit(1);
	} 
	ipmulti = argv[1];
	port = atoi(argv[2]);
	ttl = atoi(argv[3]);
    strcpy(str, argv[4]);

    MulticastSocket ms;
    DatagramPacket packet(str, strlen(str) + 1, ipmulti, port);
    try {
        ms.send(packet, ttl);
    } catch (string msg) {
        cout << msg << endl;
    }
    return 0;
}
