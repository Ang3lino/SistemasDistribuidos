
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <iostream>

const int MAX_UDP_LENGTH = 4000;
enum OperationId: int { SUM=1 };
enum MessageType: int { REQUEST=1, REPLY };

struct Message {
    MessageType messageType; // 0 = Solicitud, 1 = Respuesta
    unsigned requestId;
    OperationId operationId; //Identificador del mensaje
    char arguments[MAX_UDP_LENGTH]; //Identificador de la operacion
    size_t size;
};


#endif
