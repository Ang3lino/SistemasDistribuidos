#include "Solicitud.h"

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/*    num[0] = atoi(argv[2]);
    num[1] = atoi(argv[3]);*/
int main(int argc, char *argv[]) {
    int num[] = {255};
    int numRespuesta;
    int contador = 0;
    int puerto = 7200;
    char *ip = "127.0.0.1";
    int n = 5;  // atoi(argv[2]);
    Solicitud solicitud;

    while (++contador <= n) {
        char *buff = solicitud.doOperation(ip, puerto, 1, (char *) &num[0]);
        memcpy(&numRespuesta, buff, sizeof(int));
        printf("Resultado: %d\n", numRespuesta);
    }
    return 0;
}
