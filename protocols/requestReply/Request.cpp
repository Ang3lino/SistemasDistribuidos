#include "Request.h"


Request::Request() {
    sock = new DatagramSocket(0);  // ask the os to provide a port
}

Request::Request(string ip_, int port_): ip(ip_), port(port_) {
    sock = new DatagramSocket(0);
}

// ostream & operator << (ostream &out, Message &msg) {
//     out << " requestId=" << msg.requestId << "\n";
//     out << " operationId=" << msg.operationId << "\n";
//     out << " sizeof(args)=" << msg.size << "\n";
//     return out;
// }

void printMessage(Message msg) {
    cout << " requestId=" << msg.requestId << "\n";
    cout << " operationId=" << msg.operationId << "\n";
    cout << " sizeof(args)=" << msg.size << "\n";
    cout << " args" << msg.arguments << "\n";
}

char *Request::doOperation(string &ip, int port, OperationId op_id, 
        char *args, size_t arglen) {
    Message *msg = new Message();
    msg->messageType = MessageType::REQUEST;
    msg->operationId = op_id;
    msg->requestId = 1;
    msg->size = arglen;
    memcpy(msg->arguments, args, arglen);

    if (msg->operationId == OperationId::SUM) {
        DatagramPacket p((char *) msg, sizeof(Message), ip, port);
        // printMessage(*msg);
        sock->send(p);
        DatagramPacket response(NULL, sizeof(int));
        sock->receive(response);
        return response.getData();
    }
    return NULL;  // No match for que operation id requested
}

char *Request::doOperation(OperationId op_id, char *args, size_t arglen) {
    return doOperation(ip, port, op_id, args, arglen);  
}
