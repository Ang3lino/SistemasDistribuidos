#include "Reply.h"
#include <iostream>
#include <stdio.h>

using namespace std;

char *sum(char *args_) {
    int *args = (int *) args_;
    int *res = new int(1);
    *res = args[0] + args[1];
    printf("%d + %d = %d\n", args[0], args[1], *res);
    return (char *) res; 
}

int main(int argc, char const *argv[]) {
    const int port = 5400;
    Reply reply(port);
    cout << "El servido ha empezado, esperando solicitud..." << endl;
    int request_count = 0;
    while (1) {
        Message *msg = reply.getRequest();
        printf("Request %d ", ++request_count);
        if (msg->operationId == OperationId::SUM) {
            char *result = sum(msg->arguments);
            reply.sendReply(result, sizeof(int), OperationId::SUM);
        } else {
            cerr << "Operacion no reconocida" << endl;
            // send NULL
        }
    }
    puts("");
    return 0;
}
