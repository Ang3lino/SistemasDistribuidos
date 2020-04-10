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
    Message msg (MessageType::REQUEST, 1, op_id, arglen, args);
    DatagramPacket p((char *) &msg, sizeof(Message), ip, port);
    Message buff ;
    DatagramPacket response((char *) &buff, sizeof(Message));
    DatagramSocket sock;
    sock.send(p);
    sock.receive(response);
    char *result = new char(buff.argumentLength);
    memcpy((char *) result, (char *) buff.arguments, buff.argumentLength);
    return result;
}

char *Request::doOperation(OperationId op_id, char *args, size_t arglen) {
    if (timeout_set) 
        return doOperation(ip, port, op_id, args, arglen, secs, u_secs);
    return doOperation(ip, port, op_id, args, arglen);  
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

// timeout version, returns NULL if the remote methods doesn't return any argument. Throws exception if we can't reach the server
char *Request::doOperation(string &ip, int port, OperationId op_id, char *args, size_t arglen, time_t secs, long u_secs) {
    Message m_request(MessageType::REQUEST, ack, op_id, arglen, args);
    char *result = NULL, serialized[MSG_LEN], unserialized[MSG_LEN];
    const int MAX_ATTEMPT = 7;
    DatagramSocket s;
    m_request.serialize(serialized);
    DatagramPacket p_request(serialized, MSG_LEN, ip, port), p_response(unserialized, MSG_LEN);
    
    cout << "Starting to send a message: \n" << m_request << endl;
    int n = -1, attempt = MAX_ATTEMPT;
    while (n < 0 && --attempt >= 0) {
        s.send(p_request);
        cout << "Message sent: \n";
        cout << m_request << endl;
        cout << "Bytes sent: \n";
        print_bytes(serialized, 0, 32);
        n = s.receiveTimeout(p_response, secs, u_secs);
        if (n > 0) {
            cout << "\nMessage received: \n";
            print_bytes(unserialized, 0, 32);
        }
    }
    if (n < 0) 
        throw std::string("The server is not available.\n");
    Message m_response(unserialized, MSG_LEN);
    ++ack;
    if (m_response.argumentLength > 0) {
        result = new char(m_response.argumentLength);
        memcpy((char *) result, (char *) m_response.arguments, m_response.argumentLength);
    }
    return result;
}

char *Request::doOperation(OperationId op_id, char *args, size_t arglen, time_t secs, long u_secs) {
    return doOperation(ip, port, op_id, args, arglen, secs, u_secs);  
}
 