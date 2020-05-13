
#include "./lib/DatagramPacket.h"
#include "./lib/DatagramSocket.h"
#include "./lib/reg_util.h"
#include "./lib/Request.h"


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


int main(int argc, char const *argv[]) {
    int n = 10000;
    const char *fname = "client.txt";
    int ack;
    registro r;
    
    if (argc == 2) n = atoi(argv[1]);
    request.setSoTimeout(2, 0);

    // get n random registers, save and read them from file
    vector<registro > registers;
    
    registers = get_random_registers(n);
    alter_regs_in_file(fname, "w", registers);
    registers = read_registers(fname, n);
    
    for (int vote_count = registers.size() - 1; vote_count >= 0; ) {
        r = registers[vote_count];
        ack = send_register(r);
        // printf("ack: %d\n", ack);
        // print_structure(&r, sizeof(r));
        if (ack >= 0) --vote_count;
    }
    return 0;
}

