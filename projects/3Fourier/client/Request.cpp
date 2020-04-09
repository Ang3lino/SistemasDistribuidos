#include "Request.h"


Request::Request() {
}

Request::Request(string ip_, int port_): ip(ip_), port(port_) {
}

void Request::setSoTimeout(long secs_, long u_secs_) {
    timeout_set = true;
    secs = secs_;
    u_secs = u_secs_;
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
    if (timeout_set) 
        return doOperation(ip, port, op_id, args, arglen, secs, u_secs);
    return doOperation(ip, port, op_id, args, arglen);  
}


void Request::send(Message &m, DatagramSocket &s) { 
    char bytes[MSG_LEN];
    m.serialize(bytes);
    DatagramPacket p(bytes, MSG_LEN, ip.c_str(), port);
    s.send(p);
    cout << "Message sent: \n";
    cout << m << endl;
    cout << "Bytes sent: \n";
    print_bytes(bytes, 0, 32);
}

int Request::receive_ack(DatagramSocket &s) {
    char msg_serialized[MSG_LEN];
    DatagramPacket response(msg_serialized, MSG_LEN);
    if (s.receive(response) == -1) {
        cout << "[!] Error with ack\n";
        return -1;
    }
    cout << "\nMessage received: \n";
    print_bytes(msg_serialized, 0, 32);
    ByteBuffer bb(msg_serialized, MSG_LEN);

    // for some reason you MUST store the values in int variables and contruct the instance with them
    int messageType = bb.readInt();
    int requestId = bb.readInt();
    int operationId = bb.readInt();
    int argumentLength = bb.readInt();
    Message resp((MessageType) messageType, requestId, (OperationId) operationId, argumentLength, (char *) NULL);
    return requestId;
}

void print_bytes(char *bytes, unsigned a, unsigned b) {
    int j = 0, count = 0;
    printf("\n%04d:   ", ++count);
    for (unsigned i = a; i < b; ++i) {
        printf("%02x ", (unsigned char) bytes[i]);
        if (++j == 16) {
            printf("\n%04d: ", ++count);
            j = 0;
        }
        if (j % 4 == 0) {
            printf("\t");
        }
    }
    std::cout << std::endl;
}

// timeout version
char *Request::doOperation(string &ip, int port, OperationId op_id, char *args, size_t arglen, time_t secs, long u_secs) {
    Message msg(MessageType::REQUEST, ack, op_id, arglen, args);
    DatagramPacket p((char *) &msg, sizeof(Message), ip, port);
    Message buff ;
    DatagramPacket response((char *) &buff, sizeof(Message));
    const int MAX_ATTEMPT = 7;
    int n = -1, attempt = MAX_ATTEMPT;
    DatagramSocket s;
    char *result;

    cout << "Starting to send a message: \n" << msg << endl;
    while (n < 0 && --attempt >= 0) {
        s.send(p);
        n = s.receiveTimeout(response, secs, u_secs);
    }
    if (n < 0) 
        throw std::string("The server is not available.\n");
    if (buff.argumentLength == 0) 
        return NULL;

    result = new char(buff.argumentLength);
    memcpy((char *) result, buff.arguments, buff.argumentLength);
    return result;
}

char *Request::doOperation(OperationId op_id, char *args, size_t arglen, time_t secs, long u_secs) {
    return doOperation(ip, port, op_id, args, arglen, secs, u_secs);  
}
 