
#ifndef __MESSAGE_H__
#define __MESSAGE_H__


const int MAX_UDP_LENGH = 4000;
enum class OperationId { SUM };
enum class MessageType { REQUEST, REPLY };

struct Message {
    MessageType messageType; // 0 = Solicitud, 1 = Respuesta
    unsigned requestId;
    OperationId operationId; //Identificador del mensaje
    char arguments[MAX_UDP_LENGH]; //Identificador de la operacion
};


#endif
