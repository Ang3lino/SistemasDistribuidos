
#include "./lib/MulticastSocket.h"
#include "./lib/Request.h"
#include "./lib/reg_util.h"

#include <iostream> // std::cout, std::cerr
#include <experimental/random> // std::experimental::randint

using namespace std;

vector<pair<string, int64_t > > 
ping(MulticastSocket msock, string multicast_ip, int receptors) 
{
    int port = 7777; 
    Request request(multicast_ip, port);
    int _;
    auto response_multicast = request.doOperationMulticast( 
            OperationId::PING, (char *) &_, sizeof(int), receptors);
    response_multicast = request.doOperationMulticast( 
            OperationId::PING, (char *) &_, sizeof(int), receptors);
    return response_multicast;
}

int main(int argc, char const *argv[]) 
{
    MulticastSocket msock;
    string multicast_ip = "224.0.0.0";
    int port = 7777;
    Request request(multicast_ip, port);
    int _;
    // Parametros posibles a modificar por la linea de comandos
    int receptors = 3;
    if (argc == 2) {
        receptors = atoi(argv[1]);
    }

    auto response_multicast = request.doOperationMulticast( 
            OperationId::PING, (char *) &_, sizeof(int), receptors);
    response_multicast = request.doOperationMulticast( 
            OperationId::PING, (char *) &_, sizeof(int), receptors);
    for (auto &res: response_multicast) {
        printf("IP: %s Time(ms): %ld\n", res.first.c_str(), res.second);
    }
    return 0;
}
