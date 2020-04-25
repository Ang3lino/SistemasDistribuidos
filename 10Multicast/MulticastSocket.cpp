#include "MulticastSocket.h"


MulticastSocket::MulticastSocket(): DatagramSocket() {}

MulticastSocket::MulticastSocket(uint16_t iport): DatagramSocket(iport) {}

MulticastSocket::~MulticastSocket() {}

static void initMulticast(struct ip_mreq &multicast, uint16_t iport, const char *multicastIp) {
    multicast = {0};  // for C99 onwards
	multicast.imr_multiaddr.s_addr = inet_addr(multicastIp);
	multicast.imr_interface.s_addr = htons(iport);
}

/** iport must be 0 if we are goint to receive data.
 * addr must be between 224.0.0.0, 239.255.255.255
 */
void MulticastSocket::joinGroup(uint16_t iport, const std::string &addr) {
    initMulticast(groupAddr, iport, addr.c_str());
    int ok = setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &groupAddr, sizeof(groupAddr));
	if (ok < 0) {
        cout << errno << endl;
		cerr << std::string("Cannot join group: ") + std::string(strerror(errno));
        exit(1);
    }
}

void MulticastSocket::leaveGroup(uint16_t iport, const std::string &addr) {
    initMulticast(groupAddr, iport, addr.c_str());
    int ok = setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &groupAddr, sizeof(groupAddr)) ;
	if (ok < 0) {
		cerr <<  std::string("Cannot leave group: ") + std::string(strerror(errno));
        exit(1);
    }
}

int MulticastSocket::send(DatagramPacket &p, uint8_t ttl) {
	setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &ttl, sizeof(ttl));
	return DatagramSocket::send(p);
}

int MulticastSocket::send_unicast(DatagramPacket &p) {
	return DatagramSocket::send(p);
}

int MulticastSocket::receive(DatagramPacket &p) { 
    return DatagramSocket::receive(p); 
}

int MulticastSocket::receiveTimeout(DatagramPacket &p, time_t seconds, suseconds_t microseconds) {
	return DatagramSocket::receiveTimeout(p, seconds, microseconds);
}

