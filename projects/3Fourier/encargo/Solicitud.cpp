#include <iostream>
#include <cstring>
#include "Solicitud.h"

using namespace std;

Solicitud::Solicitud() {
    socketlocal = new SocketDatagrama(0);
}

void 
init_mensaje(struct mensaje &msg, int msgType, int reqId, int opId) {
    msg.messageType = msgType;
    msg.requestId = reqId;
    msg.operationId = opId;
}

char *
Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments) {  //Usuario cliente (puerto variable)
    int enviado, recibido;
    cout << "doOperation" << endl;
    cout << arguments << endl;

    struct mensaje msg;
    init_mensaje(msg, 0, 0, operationId);
    memcpy(msg.arguments, arguments, TAM_MAX_DATA);
    PaqueteDatagrama p = PaqueteDatagrama((char *) &msg, sizeof(struct mensaje), IP, puerto);
    cout << "Datos enviados" << endl;
    cout << "IP: " << p.obtieneDireccion() << endl;
    cout << "Puerto: " << p.obtienePuerto() << endl;
    enviado = socketlocal->envia(p);
    if (enviado == -1) {
        perror("Fallo al enviar");
    }
    PaqueteDatagrama pRes = PaqueteDatagrama(puerto);

    recibido = socketlocal->recibeTimeout(pRes, 2, 500);
    int contador = 1;

    while (contador < 7 && recibido == -1) {
        socketlocal->envia(p);
        recibido = socketlocal->recibeTimeout(pRes, 2, 500);
        cout << "Intento número : " << contador << ' ';
        contador++;
    }

    if (contador == 7) {
        cout << "Fallo al enviar" << endl;
        exit(0);
    } 
    cout << "Datos recibidos" << endl;
    cout << "IP: " << pRes.obtieneDireccion() << endl;
    cout << "Puerto: " << pRes.obtienePuerto() << endl;

    struct mensaje *msgR = (struct mensaje *) pRes.obtieneDatos();

    return (char *) msgR->arguments;
}
