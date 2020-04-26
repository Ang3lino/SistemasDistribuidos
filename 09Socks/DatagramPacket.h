
#ifndef __DatagramPacket_H__
#define __DatagramPacket_H__

#include <cstddef>
#include <string>
#include <string.h>

using namespace std;

class DatagramPacket {
public:
    // data, len, ip, port
    DatagramPacket(char* , size_t, const string &, uint16_t );
    DatagramPacket(char* , size_t);
    ~DatagramPacket();
    string getAddress();
    char *getData();
    size_t getLength();
    uint16_t getPort();

    void setAddress(const string &);
    void setData(char* , size_t);
    void setLength(size_t);
    void setPort(uint16_t);

private:
    char *data;
    uint16_t port;
    string ip;
    size_t length;
};

#endif