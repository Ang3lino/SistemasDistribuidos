
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
    int n = 1000;
    // Parametros posibles a modificar por la linea de comandos
    int receptors = 3;
    if (argc == 3) {
        n = atoi(argv[1]);
        receptors = atoi(argv[2]);
    }

    vector<registro > registros = get_random_registers(n);

    for (auto &reg: registros) {
        int status = request.doOperationMulticast( 
                OperationId::SEND_REG_OP, 
                (char *) &reg, sizeof(registro), receptors);
    }

    return 0;
}
