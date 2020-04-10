
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "ByteBuffer.h"

const int ARG_LEN = 4096;
enum OperationId: int { UNKNOWN=-1, SUM=1, PLOT, SET_X_AXIS, DUMMY };
enum MessageType: int { REQUEST=1, REPLY };

struct Message {
    MessageType messageType; // Solicitud, Respuesta
    int requestId;
    OperationId operationId; //Identificador del mensaje
    int argumentLength;
    char arguments[ARG_LEN]; 
    // char *arguments;
    void serialize(char *);

    Message(MessageType , int , OperationId , int , char *);
    Message(char *, unsigned);
    Message();

    friend std::ostream & operator << (std::ostream &, const Message &);
};

constexpr int MSG_LEN = sizeof(Message);

#endif
