
#include "./lib/DatagramPacket.h"
#include "./lib/DatagramSocket.h"
#include "./lib/reg_util.h"
#include "./lib/Request.h"

#include "Trie.cpp"

const int PORT = 5400;
const string IP = "127.0.0.1";

Request request(IP, PORT);

int send_register(registro &r) {
    int *ack_ptr = (int *) 
            request.doOperation(OperationId::SEND_REG_OP, (char *) &r, sizeof(r));
    if (ack_ptr == nullptr) 
        return -1;
    int ack = *(int *) ack_ptr;
    delete ack_ptr;
    return ack;
}

void test(Trie &trie, string key) {
    trie.put(key, true);
    bool result = trie.get(key);
    cout << result;
    cout << endl;
}

int main(int argc, char const *argv[]) {
    Trie trie;

    test(trie, "she");
    test(trie, "sells");
    test(trie, "shells");
    test(trie, "the");
    test(trie, "sea");
    test(trie, "shore");

    test(trie, "she");

    string key = "hola";
    bool result = trie.get(key);
    cout << result;

    key = "shit";
    result = trie.get(key);
    cout << result;

    key = "shingeki";
    result = trie.get(key);
    cout << result;


    cout << endl;
    return 0;
}

