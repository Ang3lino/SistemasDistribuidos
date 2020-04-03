#ifndef __REPLY_H__
#define __REPLY_H__

#include <chrono>
#include <thread>

#include "DatagramSocket.h"
#include "Message.h"


class Reply{
public:
    Reply(int);  // port
    Message *getRequest(void);
    void sendReply(char *reply, size_t arglen, OperationId operation) ;
private:
    DatagramSocket *sock;
    string addr;
    int port;
};


#endif
