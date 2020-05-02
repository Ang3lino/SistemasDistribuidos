
#include "./lib/DatagramPacket.h"
#include "./lib/DatagramSocket.h"
#include "./lib/reg_util.h"


void send_register(registro r) {
    uint16_t port = 5400;
    string ip = "127.0.0.1";
    DatagramPacket pack((char *) &r, sizeof(registro), ip, port);
    DatagramSocket sock;
    sock.send(pack);
}

int main(int argc, char const *argv[]) {
    const char *fname = "client.txt";
    registro r = read_first_register(fname);
    send_register(r);
    puts("Registro enviado");
    print_structure(&r, sizeof(r));
    return 0;
}

