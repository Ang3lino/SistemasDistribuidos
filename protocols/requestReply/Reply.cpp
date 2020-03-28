
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

Message *newMessage(MessageType type, int request, OperationId op, char *args, int arglen) {
    Message *msg = new Message;
    msg->messageType = type;
    msg->requestId = request;
    msg->operationId = op;
    memcpy(msg->arguments, args, arglen);
    return msg;
}

void Reply::sendReply(char *reply, size_t arglen, OperationId operation) {
    Message *buff = newMessage(MessageType::REPLY, 1, operation, reply, arglen);
    DatagramPacket response((char *) buff, sizeof(Message), addr, port);
    sock->send(response);
}
