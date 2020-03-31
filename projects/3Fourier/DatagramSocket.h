
#ifndef __DatagramSocket_H__
#define __DatagramSocket_H__


#ifdef linux
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#else
	#include <ws2tcpip.h>
	// #pragma comment(lib,"ws2_32.lib") // Winsock Library, it only works in the microsoft compiler, MinGW ignores it
#endif

#include <iostream>
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
	void setTimeout(long, long);
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
