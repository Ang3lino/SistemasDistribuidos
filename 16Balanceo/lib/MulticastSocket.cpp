#include "MulticastSocket.h"


MulticastSocket::MulticastSocket(): DatagramSocket() {}

MulticastSocket::MulticastSocket(uint16_t iport): DatagramSocket(iport) {}

MulticastSocket::~MulticastSocket() {}

// reliable methods
int MulticastSocket::sendReliable(DatagramPacket &p, uint8_t ttl, int receptors) {
    int n_tries = 7;
    DatagramSocket::setTimeout(7, 0);
    while (n_tries--) {
        const int send_code = send(p, ttl);
        if (send_code < 0) {
            cerr << ("Cannot send");
            exit(EXIT_FAILURE);
        }
        int successful_delivery = 0;
        for (int i = receptors; i; --i) {
            int response = 0;
            DatagramPacket pack((char *) &response, sizeof(response));
            int receive_code = DatagramSocket::receive(pack);
            if (0 < receive_code && response == 1)
                ++successful_delivery;
            else 
                break;
        }
        if (successful_delivery == receptors) 
            return 1;
    }
    return -1;
}

int MulticastSocket::receiveReliable(DatagramPacket &p) {
    long secs = 15, u_secs = 0;
    DatagramSocket::setTimeout(secs, u_secs);
    int receive_code = DatagramSocket::receive(p);
    int send_code = 1;
    DatagramPacket reply_pack((char *) &send_code, sizeof(send_code), p.getAddress(), p.getPort());
    DatagramSocket::send(reply_pack);
    return receive_code;
}

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

// int MulticastSocket::receiveTimeout(DatagramPacket &p, time_t seconds, suseconds_t microseconds) {
// 	return DatagramSocket::receiveTimeout(p, seconds, microseconds);
// }

