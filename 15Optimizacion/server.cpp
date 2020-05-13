
#include "./lib/DatagramPacket.h"
#include "./lib/DatagramSocket.h"
#include "./lib/reg_util.h"
#include "./lib/Message.h"
#include "./lib/Reply.h"

#include "Trie.cpp"

#include <set>
#include <algorithm>
#include <functional>

const uint16_t PORT = 5400;
set<int> hist;
Reply reply(PORT);  // !!
Trie<struct timeval > trie;

// comendanto esta deficion se permitiran o no los votos repetidos
#define reg_repeated_not_allowed 1
enum SearchOption: int { LINEAR=0, BINARY, TRIE };


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
    for (auto r: registers) {
        cel = string(r.celular);
        trie.put(cel, r.timestamp);
    }
    cout << "Datos cargados en la estructura trie. \n";
}

vector<registro > load_db(const char *fname, int n) {
    vector<registro > registers;
    try {
        registers = read_registers(fname, n);
    } catch (const char *e) {
        printf("No se encontro el archivo %s. \n", fname);
        return registers;
    }
    load_regs_in_trie(registers);
    return registers;
}

bool 
parse_args (int argc, char const *argv[], int &n, SearchOption &option) 
{
    if (argc == 3) {
        n = atoi(argv[1]);
        int choice = atoi(argv[2]);
        switch (choice) {
            case 0: option = SearchOption::LINEAR; break;
            case 1: option = SearchOption::BINARY; break;
            default: option = SearchOption::TRIE; break;
        }
        return true;
    } 
    return false;   
} 

namespace reg {
    bool less_than(const registro &r, const registro &s) {
        return strcmp(r.celular, s.celular) < 0;
    }

    bool equals(const registro &r, const registro &s) {
        return strcmp(r.celular, s.celular) == 0;
    }
}


bool 
reg_in_file(SearchOption option, const registro &r, 
        vector<registro > &registers) {
    auto begin = registers.begin();
    auto end = registers.end();
    if (option == SearchOption::LINEAR)
        return find_if(
            begin, end, bind(reg::equals, placeholders::_1, r)) != end;
    if (option == SearchOption::BINARY) {
        sort(registers.begin(), registers.end(), reg::less_than);
        return binary_search(
            registers.begin(), registers.end(), r, reg::less_than);
    }
    return trie.has(string(r.celular)); 
}

int main(int argc, char const *argv[]) {
    int n = 10000; 
    const char *fname = "server.txt" ;
    bool repeated_req = false;
    registro r;
    SearchOption option = SearchOption::BINARY;
    parse_args(argc, argv, n, option);
    vector<registro > registers = load_db(fname, n);
    string cel;

    FILE *fp = fopen(fname, "a+");
    puts("Esperando registros...");
    for (int vote_count = n; vote_count; ) {
        receive_register(r, repeated_req);
        if (!repeated_req) {  // avoid repeated requests
            if (!reg_in_file(option, r, registers))  {
                alter_struct_in_file(fp, &r, sizeof(r));
                cel = string(r.celular);
                trie.put(cel, r.timestamp);
                registers.push_back(r);
            }
            --vote_count;
        }
    }
    fclose(fp);
    cout << endl;

    return 0;
}

