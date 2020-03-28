
#ifndef __DatagramSocket_H__
#define __DatagramSocket_H__


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

#include "DatagramPacket.h"

class DatagramSocket {
public:
	DatagramSocket();
	DatagramSocket(uint16_t iport);
	DatagramSocket(uint16_t iport, const std::string & addr);
	~DatagramSocket();
	void unbind();
	int send(DatagramPacket &p);
	int receive(DatagramPacket &p);

private:
	struct sockaddr_in localAddress;
	struct sockaddr_in remoteAddress;
	int s;
};

#endif
