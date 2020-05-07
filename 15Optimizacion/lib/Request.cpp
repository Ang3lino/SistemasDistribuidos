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

char *
Request::doOperation(string &ip, int port, OperationId op_id, char *args, size_t arglen) 
{
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


// Timeout version, returns nullptr if error.
char *
Request:: doOperation(string &ip, int port, OperationId op_id, char *args, size_t arglen, 
        time_t secs, long u_secs) {
    Message m_request(MessageType::REQUEST, ack, op_id, arglen, args);
    Message m_response;
    DatagramPacket p_req((char *) &m_request, sizeof(Message), ip, port);
    DatagramPacket p_res((char *) &m_response, sizeof(Message));
    DatagramSocket sock;
    int MAX_ATTEMPT = 7, n = -1, attempt = MAX_ATTEMPT;

    sock.setTimeout(secs, u_secs);
    while (n < 0 && --attempt >= 0) {
        sock.send(p_req);
        n = sock.receive(p_res);
    }
    if (n > 0) {
        char *result = new char(m_response.argumentLength);
        memcpy(result, m_response.arguments, m_response.argumentLength);
        ++ack;
        return result;  // you may want to use unique<char *>
    }
    return nullptr;
}

char *Request::doOperation(OperationId op_id, char *args, size_t arglen, time_t secs, long u_secs) {
    return doOperation(ip, port, op_id, args, arglen, secs, u_secs);  
}

char *Request::doOperation(OperationId op_id, char *args, size_t arglen) {
    if (timeout_set) 
        return doOperation(ip, port, op_id, args, arglen, secs, u_secs);
    return doOperation(ip, port, op_id, args, arglen);  
}

 