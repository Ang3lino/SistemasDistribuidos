
#include "Reply.h"


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
    return msg;
}

void Reply::sendReply(char *reply, size_t arglen, OperationId operation) {
    Message buff(MessageType::REPLY, 1, operation, arglen, reply);
    DatagramPacket response((char *) &buff, sizeof(Message), addr, port);
    sock->send(response);
}

