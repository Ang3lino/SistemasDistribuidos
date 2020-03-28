
#include "Reply.h"

// class Reply{
// public:
//     Reply(int);  // port
//     Message *getRequest(void);
//     void sendReply(char *respuesta);
// private:
//     DatagramSocket *socketlocal;
// };

void printMessage(Message msg) {
    cout << " requestId=" << msg.requestId << "\n";
    cout << " operationId=" << msg.operationId << "\n";
    cout << " sizeof(args)=" << msg.size << "\n";
    cout << " args" << msg.arguments << "\n";
}

Reply::Reply(int port) {
    sock = new DatagramSocket(port);
}

Message *Reply::getRequest(void) {
    Message *msg = new Message();
    DatagramPacket p((char *) msg, sizeof(Message));
    sock->receive(p);
    addr = p.getAddress();
    port = p.getPort();
    msg = (Message *) p.getData();
    // printMessage(*msg);
    return msg;
}

void Reply::sendReply(char *reply) {
    DatagramPacket response(reply, sizeof(reply), addr, port);
    sock->send(response);
}
