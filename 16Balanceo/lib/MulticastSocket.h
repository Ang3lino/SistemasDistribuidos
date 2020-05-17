
#ifndef __MulticastSocket_H__
#define __MulticastSocket_H__

#include "DatagramPacket.h"
#include "DatagramSocket.h"

#include <cstddef>
#include <string>
#include <arpa/inet.h>
#include <string.h>

class MulticastSocket : DatagramSocket {
public:
    MulticastSocket();
    MulticastSocket(uint16_t iport);

    ~MulticastSocket();

    void joinGroup(uint16_t iport, const std::string &addr);
    void leaveGroup(uint16_t iport, const std::string &addr);

    int send(DatagramPacket &p, uint8_t ttl);
    int send_unicast(DatagramPacket &p);
    void setTimeout(long secs, long u_secs);

    // reliable methods
    int sendReliable(DatagramPacket &p, uint8_t ttl, int receptors);
    int receiveReliable(DatagramPacket &p);

    int receive(DatagramPacket &p);
    int receiveTimeout(DatagramPacket &p, time_t seconds, suseconds_t microseconds);

private:
    struct ip_mreq groupAddr;
};


#endif
