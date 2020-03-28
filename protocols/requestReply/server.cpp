#include "Reply.h"
#include <iostream>

using namespace std;

char *sum(char *args_) {
    int *args = (int *) args_;
    int *res = new int(1);
    *res = args[0] + args[1];
    cout << args << endl;
    cout << res << endl;
    return (char *) res; 
}

int main(int argc, char const *argv[])
{
    const int port = 5400;
    // DatagramSocket server(port);
    // DatagramPacket request(NULL, 2*sizeof(int));
    // server.receive(request);
    // int *nums = (int *) request.getData();
    // cout << "numeros: " << nums[0] << ", " << nums[1] << endl;
    // int sum = nums[0] + nums[1];
    // DatagramPacket result((char *) &sum, sizeof(sum), request.getAddress(), request.getPort());
    // server.send(result);
    Reply reply(port);
    cout << "El servido ha empezado, esperando solicitud..." << endl;
    Message *msg = reply.getRequest();
    if (msg->operationId == OperationId::SUM) {
        reply.sendReply(sum(msg->arguments));
    } else
        reply.sendReply(NULL); 
    return 0;
}
