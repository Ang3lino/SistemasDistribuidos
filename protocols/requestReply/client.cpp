#include "Request.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    int arr[2] = {123, 246};
    string ip("127.0.0.1");
    uint16_t port = 5400;
    // DatagramPacket dp_numbers((char *) &arr[0], 2 * sizeof(int), "127.0.0.1", port);
    // DatagramPacket result(NULL, sizeof(int));
    // DatagramSocket client;
    // client.send(dp_numbers);
    // int n = client.receive(result);
    // int *ans = (int *) result.getData();
    // cout << ans[0] << endl;
    Request request(ip, port);
    int *result = (int *) request.doOperation(OperationId::SUM, (char *) arr, sizeof(arr));
    if (result == NULL) {
        cerr << "NULL returned";
        exit(1);
    }
    cout << *result << endl;
    return 0;
}
