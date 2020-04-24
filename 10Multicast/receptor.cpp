#include <bits/stdc++.h>

#include "MulticastSocket.h"

using namespace std;


int main(int argc, char const *argv[]) {
	string ipmulti;
	char str[100];
	int port, ttl;
	printf("[%s] [MULTICAST] [PORT]\n", argv[0]);
	cin >> ipmulti >> port;
	try {
		MulticastSocket ms(port);
		ms.joinGroup(0, ipmulti);
		DatagramPacket packet(str, sizeof(str));
		ms.receiveTimeout(packet, 3, 0);
		cout << packet.getAddress() << endl;
		cout << packet.getPort() << endl;
		cout << packet.getLength() << endl;
		cout << str << endl;
	} catch (string msg) {
		cout << msg << endl;
	}
	return 0;
}
