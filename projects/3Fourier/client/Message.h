
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <iostream>
#include <cstdlib>
#include <cstring>


const int MAX_UDP_LENGTH = 4096;
enum OperationId: int { UNKNOWN=-1, DUMMY=3, SUM=1 };
enum MessageType: int { REQUEST=1, REPLY };

struct Message {
    MessageType messageType; // Solicitud, Respuesta
    int requestId;
    OperationId operationId; //Identificador del mensaje
    int argumentLength;
    char arguments[MAX_UDP_LENGTH]; 
    // char *arguments;

    Message(MessageType , int , OperationId , int , char *);
    Message();

    friend std::ostream & operator << (std::ostream &, const Message &);
};

#endif
