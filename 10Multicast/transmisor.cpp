
#include <bits/stdc++.h>

#include "MulticastSocket.h"

using namespace std;


int main(int argc, const char *argv[]) {
    string ipmulti;
    char str[100];
    int port, ttl;
    printf("[%s] [MULTICAST] [PORT] [TTL]\n\n", argv[0]);
    cin >> ipmulti >> port >> ttl >> str;
    MulticastSocket ms;
    DatagramPacket packet(str, strlen(str) + 1, ipmulti, port);
    try {
        ms.send(packet, ttl);
    } catch (string msg) {
        cout << msg << endl;
    }
}
