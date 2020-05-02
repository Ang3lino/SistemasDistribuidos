
#include "./lib/DatagramPacket.h"
#include "./lib/DatagramSocket.h"
#include "./lib/reg_util.h"


registro receive_register() {
    uint16_t port = 5400;
    registro r;
    DatagramPacket pack((char *) &r, sizeof(registro));
    DatagramSocket sock(port);
    sock.receive(pack);
    return r;
}

int main(int argc, char const *argv[]) {
    const char *fname = "server.txt";
    vector<registro> registros;

    puts("Esperando registro...");
    registro r = receive_register();
    registros.push_back(r);
    save_registers(fname, registros);
    
    puts("Estructura salvada");
    print_structure(&r, sizeof(registro));
    return 0;
}

