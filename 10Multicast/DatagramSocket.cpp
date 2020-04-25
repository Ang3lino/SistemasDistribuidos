#include "DatagramSocket.h"


DatagramSocket::DatagramSocket(): DatagramSocket(0) {}

DatagramSocket::DatagramSocket(uint16_t iport): DatagramSocket(iport, "0.0.0.0") {}

DatagramSocket::DatagramSocket(uint16_t iport, const std::string &addr): timeout_set(false) {
	#ifdef _WIN32  // detect windows of 32 and 64 bits
	WSAData wsaData;
	WORD word = MAKEWORD(2, 2);
	if (WSAStartup(word, &wsaData) != 0) {
		std::cerr << "Server: WSAStartup failed with error: " << WSAGetLastError() << std::endl;
		exit(1);
	}
	#endif 

	// s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	localAddress = {0};

	int reuse = 1; // reuse the port, test with multicast can be done in localhost
	if (setsockopt(s, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1) {
		perror("Error al llamar a la función setsockopt\n");
		exit(1);
	} 

	localAddress.sin_family = AF_INET;
	localAddress.sin_addr.s_addr = inet_addr(addr.c_str());
	localAddress.sin_port = htons(iport);
	bind(s, (struct sockaddr *) &localAddress, sizeof(localAddress));
}


DatagramSocket::~DatagramSocket() {
	unbind();
}

void DatagramSocket::unbind() {
	#ifdef __linux__
	close(s);
	s = 0;
	#else 
	closesocket(s);
	WSACleanup();
	#endif
}

int DatagramSocket::receive(DatagramPacket &p) {
	if (timeout_set) 
		return receiveTimeout(p, timeout.tv_sec, timeout.tv_usec);
	#ifdef __linux__
	socklen_t len = sizeof(remoteAddress);
	#else 
	int len = sizeof(remoteAddress);
	#endif
	int n = recvfrom(s, p.getData(), p.getLength(), 0, (struct sockaddr *) &remoteAddress, &len);
	p.setPort(ntohs(remoteAddress.sin_port));
	p.setAddress(std::string(inet_ntoa(remoteAddress.sin_addr)));
	p.setLength(n);
	return n;
}

void DatagramSocket::setTimeout(long secs, long u_secs) {
    timeout = { 
        .tv_sec = secs, 
        .tv_usec = u_secs };  
    timeout_set = true;

    #ifdef _WIN32
    DWORD dw = (secs * 1000) + ((u_secs + 999) / 1000);
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *) &dw, sizeof(dw));
    #else
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(struct timeval));
    #endif
}

int DatagramSocket::receiveTimeout(DatagramPacket &p, time_t secs, time_t u_secs) {
	#ifdef __linux__
	socklen_t len = sizeof(remoteAddress);
	#else 
	int len = sizeof(remoteAddress);
	#endif
    int n = recvfrom(s, p.getData(), p.getLength(), 0, (struct sockaddr *) &remoteAddress, &len);
    if (n < 0) {  // deal with errors 
        #ifdef _WIN32
		int errcode = WSAGetLastError();
        if (errcode == WSAETIMEDOUT) 
        #else
		int errcode = errno;
        if (errcode == EAGAIN || errcode == EWOULDBLOCK)
        #endif
            std::cout << "Timeout!" << std::endl;
        else 
            std::cerr << "Error in recvfrom, error code " << errcode  << std::endl;
        return -1;
    }
    p.setPort(ntohs(remoteAddress.sin_port));  
    p.setAddress(string(inet_ntoa(remoteAddress.sin_addr)));
    p.setLength(n);
    return n;
}

int DatagramSocket::send(DatagramPacket &p) {
	// bzero((char *)&remoteAddress, sizeof(remoteAddress));
	memset((char *) &remoteAddress, 0, sizeof(remoteAddress));

	remoteAddress.sin_family = AF_INET;
	remoteAddress.sin_port = htons(p.getPort());
	remoteAddress.sin_addr.s_addr = inet_addr(p.getAddress().c_str());
	return sendto(s, p.getData(), p.getLength(), 0, (struct sockaddr*) &remoteAddress, sizeof(remoteAddress));
}
