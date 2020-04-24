
#include "DatagramPacket.h"

DatagramPacket::DatagramPacket(char *buf, size_t len): port(0), ip("") {
	setData(buf, len);
}

DatagramPacket::DatagramPacket(char *buf, size_t len, const string & addr, uint16_t iport) {
	setData(buf, len);
	setAddress(addr);
	setPort(iport);
}

string DatagramPacket::getAddress() { return ip; }

uint16_t DatagramPacket::getPort() { return port; }

char* DatagramPacket::getData() { return data; }

size_t DatagramPacket::getLength() { return length; }

// AVOID INLINE keyword in member functions! 
void DatagramPacket::setAddress(const string & addr) { ip = addr; }
void DatagramPacket::setPort(uint16_t iport) { port = iport; }
void DatagramPacket::setLength(size_t len) { length = len; }

void DatagramPacket::setData(char* buf, size_t len) {
	data = buf;
	setLength(len);
}

std::ostream& operator << (std::ostream &out, const DatagramPacket &p) {
    out << "DatagramPacket: \n";
    out << "\tport: " << p.port << "\n";
    out << "\taddress: " << p.ip << "\n";
    out << "\tlength: " << p.length << "\n";
    return out; 
}

