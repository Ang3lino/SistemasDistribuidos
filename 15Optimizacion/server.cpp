
#include "./lib/DatagramPacket.h"
#include "./lib/DatagramSocket.h"
#include "./lib/reg_util.h"
#include "./lib/Message.h"
#include "./lib/Reply.h"

#include "Trie.cpp"

#include <set>

const uint16_t PORT = 5400;
set<int> hist;
Reply reply(PORT);  // !!
Trie<struct timeval > trie;

template<typename T>
bool contains(set<T> s, T e) {
    return s.count(e) > 0;
}

void receive_register(registro &r, bool &repeated) {
    Message *msg = reply.getRequest();
    repeated = contains(hist, msg->requestId);
    if (!repeated) {
        hist.insert(msg->requestId);
        memcpy(&r, msg->arguments, msg->argumentLength);
    }
    int ack = msg->requestId;
    reply.sendReply((char *) &ack, sizeof(int), OperationId::SEND_REG_OP);
    delete msg;
}

void test(Trie<string> &trie, string key, string value) {
    trie.put(key, value);
    auto result = trie.get(key);
    cout << result;
    cout << endl;
}

void load_regs_in_trie(vector<registro> &registers) {
    string cel;
    for (auto &r: registers) {
        cel = string(r.celular);
        trie.put(cel, r.timestamp);
    }
    cout << "Datos cargados en la estructura trie. \n";
}

int main(int argc, char const *argv[]) {
    int n = 10000; 
    const char *fname = "server.txt" ;
    bool repeated_req = false;
    registro r;

    if (argc == 2) n = atoi(argv[1]);
    auto registers = read_registers(fname, n);
    load_regs_in_trie(registers);

    puts("Esperando registros...");
    for (int vote_count = n; vote_count; ) {
        receive_register(r, repeated_req);
        if (!repeated_req) {  // avoid repeated requests
            if (!trie.has(string(r.celular)))  // avoid repeated votes
                alter_reg_in_file(fname, "a+", r);
            // else
            //     cout << "Voto repetido\n";
            --vote_count;
        }
    }
    cout << endl;
    return 0;
}

