#include "DatagramSocket.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    const int port = 5400;
    DatagramSocket server(port);
    DatagramPacket request(NULL, 2*sizeof(int));
    server.receive(request);
    int *nums = (int *) request.getData();
    cout << "numeros: " << nums[0] << ", " << nums[1] << endl;
    int sum = nums[0] + nums[1];
    DatagramPacket result((char *) &sum, sizeof(sum), request.getAddress(), request.getPort());
    server.send(result);
    return 0;
}
