
// Author: Angel Manriquez

#include "MulticastSocket.h"
#include "pack_t.h"

#include <iostream> // std::cout, std::cerr
#include <experimental/random> // std::experimental::randint


using namespace std;


int main(int argc, char const *argv[]) {
    uint8_t ttl = 3;
    MulticastSocket msock;
    pack_t frame;
    string multicast_ip = "224.0.0.0";
    int port = 7777;

    // Parametros posibles a modificar por la linea de comandos
    int receptors = 3;
    unsigned deposits_amount = 1000;
    if (argc == 3) {
        deposits_amount = atoi(argv[1]);
        receptors = atoi(argv[2]);
    }

    frame.data_len = 4; // 4 bytes como datos a enviar
    frame.msg_type = 0; // emision, recepcion. En esta practica no es relevante
    for (uint i = 0; i < deposits_amount; ++i) {
        frame.ack = i; // el campo ack puede ser obviado
        frame.id = i;
        frame.data[0] = experimental::randint(1, 9); // [a, b]
        DatagramPacket packet(
                (char *) &frame, sizeof(frame), multicast_ip, port);
        int send_code = msock.sendReliable(packet, ttl, receptors);
        if (send_code < 0) {
            cerr << "Ha ocurrido un error al enviar los datos \n";
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}


