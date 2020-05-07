
#include "./lib/DatagramPacket.h"
#include "./lib/DatagramSocket.h"
#include "./lib/reg_util.h"
#include "./lib/Message.h"
#include "./lib/Reply.h"

#include <set>

const uint16_t PORT = 5400;
set<int> hist;
Reply reply(PORT);  // !!

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

int main(int argc, char const *argv[]) {
    int n = 15;
    const char *fname = "server.txt";
    bool repeated = false;
    registro r;

    if (argc == 2) n = atoi(argv[1]);
    puts("Esperando registros...");
    for (int vote_count = n; vote_count; ) {
        receive_register(r, repeated);
        if (!repeated) {
            // print_structure(&r, sizeof(r));
            alter_reg_in_file(fname, "a+", r);
            --vote_count;
        }
        // printf("Registro %s\n\n", repeated ? "repetido": "nuevo");
    }
    
    return 0;
}

