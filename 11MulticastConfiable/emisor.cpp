
#include "pack_t.h"
#include "MulticastSocket.h"

#include <iostream>
#include <memory>
#include <experimental/random>


using namespace std;


int main(int argc, char const *argv[]) {
    uint8_t ttl = 3;
    int receptors = 3;
    MulticastSocket msock;
    pack_t frame;

    // "hyperparameters"
    string multicast_ip = "224.0.0.0";
    int port = 7777;
    unsigned deposits_amount = 8;

    frame.data_len = 4;
    frame.msg_type = 0;
    for (uint i = 0; i < deposits_amount; ++i) {
        frame.ack = i;
        frame.id = i;
        frame.data[0] = experimental::randint(1, 9); // [a, b]
        DatagramPacket packet((char *) &frame, sizeof(frame), multicast_ip, port);
        int send_code = msock.sendReliable(packet, ttl, receptors);
        if (send_code < 0) {
            cerr << "Ha ocurrido un error al enviar los datos \n";
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}


