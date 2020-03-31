
#ifndef __DatagramSocket_H__
#define __DatagramSocket_H__


#ifdef linux
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#else
	#include <ws2tcpip.h>
#endif

#include <strings.h>
#include <unistd.h>

#include <errno.h>
#include "DatagramPacket.h"

class DatagramSocket {
public:
	DatagramSocket();
	DatagramSocket(uint16_t iport);
	DatagramSocket(uint16_t iport, const std::string & addr);
	~DatagramSocket();

	void unbind();

	int send(DatagramPacket &);
	int receive(DatagramPacket &);
	
	// secs, usecs
	void setTimeout(time_t, time_t);
	// DatagramPacket, secs, usecs
	int receiveTimeout(DatagramPacket &, time_t, time_t);
private:
	struct sockaddr_in localAddress;
	struct sockaddr_in remoteAddress;

	struct timeval timeout;
	bool timeout_set;
	#ifdef linux
		int s;
	#else
		SOCKET s;
		struct fd_set fds;
	#endif
};

#endif
