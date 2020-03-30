
#include "Request.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    int arr[2] = {2, 2};
    string ip("127.0.0.1");
    uint16_t port = 5400;

    if (argc != 4) {
        printf("[%s] [ip] [int] [int]", argv[0]);
        printf("Se ejecutara en el localhost, sumando %d con %d", arr[0], arr[1]);
    } else {
        ip = argv[1];
        arr[0] = atoi(argv[2]);
        arr[1] = atoi(argv[3]);
    }

    Request request(ip, port);
    int *result = (int *) request.doOperation( OperationId::SUM, (char *) arr, sizeof(arr), 2, 0);
    if (result == NULL) {
        cerr << "NULL returned";
        exit(1);
    }
    printf("%d + %d = %d\n", arr[0], arr[1], *result);
    return 0;
}
