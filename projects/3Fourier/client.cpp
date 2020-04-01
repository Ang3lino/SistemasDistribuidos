
#include "Request.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    int arr[2] = {2, 2};
    string ip("127.0.0.1");
    uint16_t port = 5400;
    int n = 1;

    if (argc != 5) {
        printf("%s [ip] [int] [int] [N_REQUEST]\n", argv[0]);
        printf("Se ejecutara en el localhost, sumando %d con %d %d veces\n", arr[0], arr[1], n);
    } else {
        ip = argv[1];
        arr[0] = atoi(argv[2]);
        arr[1] = atoi(argv[3]);
        n = atoi(argv[4]);
    }

    Request request(ip, port);
    for (int i = 0; i < n; ++i) {
        int *result = (int *) request.doOperation( OperationId::SUM, (char *) arr, sizeof(arr), 2, 0);
        if (result == NULL) 
            throw "NULL returned";
        printf("%d + %d = %d\n", arr[0], arr[1], *result);
    }
    return 0;
}
