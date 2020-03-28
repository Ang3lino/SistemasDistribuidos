#ifndef __REPLY_H__
#define __REPLY_H__

#include "DatagramSocket.h"
#include "Message.h"

class Reply{
public:
    Reply(int );  // port
    Message *getRequest(void);
    void sendReply(char *respuesta);
private:
    DatagramSocket *socketlocal;
};

#endif
