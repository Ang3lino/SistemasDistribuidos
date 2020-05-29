#include "Respuesta.h"
#include <cstring>
#include <iostream>

using namespace std;

PaqueteDatagrama p = PaqueteDatagrama(TAM_MAX_DATA);

Respuesta::Respuesta(int pl) {
    socketlocal = new SocketDatagrama(pl);
}

struct mensaje *Respuesta::getRequest(void) {
    int recibido = socketlocal->recibe(p);
    if (recibido == -1) {
        perror("Fallo al recibir");
    }
    //p.obtieneDatos();
    //msgReturn.arguments=(struct mensaje*)&p.obtieneDatos();
    //return &msgReturn;
    //return (struct mensaje*)p.obtieneDatos();
    struct mensaje *msgR = (struct mensaje *) p.obtieneDatos();

    return (struct mensaje *) p.obtieneDatos();
}

void Respuesta::sendReply(char *respuesta) {
    struct mensaje msg;
    msg.messageType = 1;
    msg.requestId = 1;
    msg.operationId = 1;
    //strcpy(msg.arguments,respuesta);
    memcpy(&msg.arguments, respuesta, sizeof(&respuesta));

    p.inicializaDatos((char *) &msg);
    cout << "\nMensaje recibido" << endl;
    cout << "Direccion: " << p.obtieneDireccion() << endl;
    cout << "Puerto: " << p.obtienePuerto() << endl;
    int enviado = socketlocal->envia(p);
    if (enviado == -1) {
        perror("Fallo al enviar");
    }
}
