#ifndef __REPLY_H__
#define __REPLY_H__

#include "DatagramSocket.h"
#include "Message.h"
#include <limits.h>

class Reply{
public:
    Reply(int);  // port
    Message *getRequest(void);
    void sendReply(char *reply, size_t arglen, OperationId operation) ;
    Message *processRequest(void) ;
private:
    DatagramSocket *sock;
    string addr;
    int port;
    unsigned last_ack;
};

#endif
