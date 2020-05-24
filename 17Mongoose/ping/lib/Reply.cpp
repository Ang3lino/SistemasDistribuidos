
#include "Reply.h"


Reply::Reply(int port) {
    sock = new DatagramSocket(port);
}

Reply::Reply() {
    last_ack = INT_MIN;
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

Message *Reply::getRequestMulticast(MulticastSocket &ms) {
    Message *msg = new Message();
    DatagramPacket p((char *) msg, sizeof(Message));
    int code = ms.receive(p);
    if (code < 0) {
        cerr << "Could not receive anything\n";
        return nullptr;
    }
    addr = p.getAddress();
    port = p.getPort();
    msg = (Message *) p.getData();
    return msg;
}

Message *Reply::processRequest(MulticastSocket &msock) {
    Message *msg = getRequestMulticast(msock);
    if (last_ack == msg->ack)
        return nullptr;
    last_ack = msg->ack;

    // send response
    Message m_res(MessageType::REPLY, msg->operationId, (char *) &last_ack, sizeof(unsigned), last_ack);
    DatagramPacket response((char *) &m_res, sizeof(Message), addr, port);
    msock.send(response);
    last_ack = INT_MIN;  // for this specific case it'll work, warning
    return msg;
}

void Reply::sendReply(char *reply, size_t arglen, OperationId operation) {
    Message buff(MessageType::REPLY, 1, operation, arglen, reply);
    DatagramPacket response((char *) &buff, sizeof(Message), addr, port);
    sock->send(response);
}

