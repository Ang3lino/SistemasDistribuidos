
// Author: Angel Manriquez
#include "./lib/MulticastSocket.h"
#include "./lib/reg_util.h"
#include "./lib/Request.h"

#include <iostream> // std::cout, std::cerr
#include <experimental/random> // std::experimental::randint

using namespace std;

int main(int argc, char const *argv[]) 
{
    MulticastSocket msock;
    string multicast_ip = "224.0.0.0";
    int port = 7777;
    Request request(multicast_ip, port);

    // Parametros posibles a modificar por la linea de comandos
    int receptors = 2;
    unsigned deposits_amount = 1000;
    if (argc == 3) {
        deposits_amount = atoi(argv[1]);
        receptors = atoi(argv[2]);
    }

    for (uint i = 0; i < deposits_amount; ++i) {
        unsigned x = experimental::randint(1, 9); // [a, b]
        cout << "numero aleatorio : " << x << endl;
        int status = request.doOperationMulticast( OperationId::SUM, (char *) &x, sizeof(unsigned), receptors);
        cout << status << endl;
    }

    return 0;
}

    // frame.data_len = 4; // 4 bytes como datos a enviar
    // frame.msg_type = 0; // emision, recepcion. En esta practica no es relevante
    // for (uint i = 0; i < deposits_amount; ++i) {
    //     frame.ack = i; // el campo ack puede ser obviado
    //     frame.id  = i;
    //     frame.data[0] = experimental::randint(1, 9); // [a, b]
    //     DatagramPacket packet(
    //             (char *) &frame, sizeof(frame), multicast_ip, port);
    //     int send_code = msock.sendReliable(packet, ttl, receptors);
    //     if (send_code < 0) {
    //         cerr << "Ha ocurrido un error al enviar los datos \n";
    //         exit(EXIT_FAILURE);
    //     }
    // }

