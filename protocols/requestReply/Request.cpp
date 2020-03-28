#include "Request.h"

// class Request {
// public:
//     Request();
//     // ip, port
//     Request(char *, int);
//     // ip, port, operationId, args
//     char *doOperation(char *, int , int , char *);
//     // operationId, args
//     char *doOperation(int, char *);
// private:
//     DatagramSocket *sock;
// };

Request::Request() {
    sock = DatagramSocket(0);  // ask the os to provide a port
}

Request::Request(string ip_, int port_): ip(ip_), port(port_) {
}

char *Request::doOperation(string &ip, int port, OperationId op_id, char *args) {
    Message msg;
    msg.messageType = MessageType::REQUEST;
    msg.operationId = OperationId::SUM;
    msg.requestId = 0;
    for (int i = 0; i < MAX_UDP_LENGH; ++i) msg.arguments[i] = args[i];
    DatagramPacket p((char *) &msg, sizeof(msg), ip, port);
    sock.send(p);
    Message msgResponse;
    DatagramPacket response(NULL, sizeof(Message));
    size_t n = sock.receive(response);
    return response.getData();
}