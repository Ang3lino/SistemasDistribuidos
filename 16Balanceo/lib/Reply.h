#ifndef __REPLY_H__
#define __REPLY_H__

#include "DatagramSocket.h"
#include "MulticastSocket.h"
#include "Message.h"
#include <limits.h>

class Reply{
public:
    Reply(); // Multicast
    Reply(int port);  // port
    Message *getRequest(void);
    Message *getRequestMulticast(MulticastSocket &ms);
    void sendReply(char *reply, size_t arglen, OperationId operation) ;
    Message *processRequest(MulticastSocket &msock);
private:
    DatagramSocket *sock;
    string addr;
    int port;
    unsigned last_ack;
};

#endif
