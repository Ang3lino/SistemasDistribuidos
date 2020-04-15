#include <iostream>
#include <cstring>
#include "Solicitud.h"

using namespace std;

Solicitud::Solicitud() 
{
    socketlocal = new SocketDatagrama(0);
}

void 
init_mensaje(struct mensaje &msg, int msgType, int reqId, int opId, char *args, int arg_len) 
{
    msg.messageType = msgType;
    msg.requestId = reqId;
    msg.operationId = opId;
    msg.argumentLength = arg_len;
    if (arg_len > 0) {
        memcpy(msg.arguments, args, arg_len);
    }
}

char *
Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments) 
{  
    struct mensaje msg;
    int recibido = -1, enviado = -1;

    // Inicializando la estructura
    init_mensaje(msg, 0, 0, operationId, arguments, TAM_MAX_DATA);
    PaqueteDatagrama p = PaqueteDatagrama((char *) &msg, sizeof(struct mensaje), IP, puerto);

    // empezando el intento de envio y recepcion
    PaqueteDatagrama pRes = PaqueteDatagrama(puerto);
    int contador = 0;
    while (++contador <= 7 && recibido == -1) {
        enviado = socketlocal->envia(p);  // returns -1 en caso de error
        if (enviado == -1) {
            puts("No se envio el mensaje adecuadamente (ya prendio el servidor?)");
            continue;
        }
        recibido = socketlocal->recibeTimeout(pRes, 10, 500);
    }
    if (contador > 7) {
        throw string("El servidor no esta disponible\n");
        cout << "Fallo al enviar" << endl;
    } 

    struct mensaje *msgR = (struct mensaje *) pRes.obtieneDatos();
    if (msgR->argumentLength > 0) {
        char *response = new char[sizeof(int)];
        memcpy(response, msgR->arguments, sizeof(int));
        return response;
    }
    return NULL;
}
