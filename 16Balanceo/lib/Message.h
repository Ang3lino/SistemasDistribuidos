
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <iostream>
#include <cstdlib>
#include <cstring>

const int ARG_LEN = 1 << 10;
enum OperationId: int { UNKNOWN=-1, DUMMY_OP=0, SUM=1, SEND_REG_OP };
enum MessageType: int { REQUEST=1, REPLY };

struct Message {
    MessageType messageType; // Solicitud, Respuesta
    int requestId;
    OperationId operationId; //Identificador del mensaje
    int argumentLength;
    char arguments[ARG_LEN]; 
    unsigned ack;

    // char *arguments;
    void serialize(char *);

    Message(MessageType , int , OperationId , int , char *);
    Message(MessageType type, OperationId opid, char *args, size_t size, unsigned ack_);
    Message(char *, unsigned);
    Message();

    friend std::ostream & operator << (std::ostream &, const Message &);
};

constexpr int MSG_LEN = sizeof(Message);

#endif
