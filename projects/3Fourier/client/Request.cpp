#include "Request.h"


Request::Request() {
}

Request::Request(string ip_, int port_): ip(ip_), port(port_) {
}

char *Request::doOperation(string &ip, int port, OperationId op_id, char *args, size_t arglen) {
    Message *msg = new Message( MessageType::REQUEST, 1, op_id, arglen, args);
    if (msg->operationId == OperationId::SUM) {
        DatagramPacket p((char *) msg, sizeof(Message), ip, port);
        Message *buff = new Message;
        DatagramPacket response((char *) buff, sizeof(Message));
        DatagramSocket sock;
        sock.send(p);
        sock.receive(response);
        return buff->arguments;
    }
    return NULL;  // No match for que operation id requested
}

char *Request::doOperation(OperationId op_id, char *args, size_t arglen) {
    return doOperation(ip, port, op_id, args, arglen);  
}

char *Request::doOperation(string &ip, int port, OperationId op_id, char *args, size_t arglen, time_t secs, long u_secs) {
    Message *msg = new Message(MessageType::REQUEST, 1, op_id, arglen, args);
    if (msg->operationId == OperationId::SUM) {
        DatagramPacket p((char *) msg, sizeof(Message), ip, port);
        Message *buff = new Message;
        DatagramPacket response((char *) buff, sizeof(Message));
        const int MAX_ATTEMPT = 7;
        int n = -1, attempt = MAX_ATTEMPT;
        DatagramSocket s;
        cout << "Starting to send a message: \n" << *msg << endl;
        while (n < 0 && --attempt >= 0) {
            s.send(p);
            n = s.receiveTimeout(response, secs, u_secs);
        }
        if (n < 0) 
            throw std::string("The server is not available.\n");
        return buff->arguments;
    }
    return NULL;  // No match for que operation id requested
}

char *Request::doOperation(OperationId op_id, char *args, size_t arglen, time_t secs, long u_secs) {
    return doOperation(ip, port, op_id, args, arglen, secs, u_secs);  
}
 