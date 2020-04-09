#include <iostream>
#include <vector>
#include <algorithm> 

#define _USE_MATH_DEFINES  // use M_PI
#include <math.h>

#include "Message.h"
#include "DatagramSocket.h"
#include "ByteBuffer.h"


using namespace std;

const int ARG_LEN = 4096;
const int PORT = 5400;
const int MESSAGE_LENGTH = sizeof(Message);
const int N_SAMPLES = 512;


void size_of_types() {
    cout << "int " << sizeof(int) << endl;
    cout << "float " << sizeof(float) << endl;
    cout << "double " << sizeof(double) << endl;
    cout << "char " << sizeof(char) << endl;
    cout << "short " << sizeof(short) << endl;
    cout << "Message " << sizeof(Message) << endl;
}

void serialize(Message *msgPacket, char *data) {
    int *q = (int *) data;    
    *q = msgPacket->messageType; q++;    
    *q++ = msgPacket->requestId;   
    *q++ = msgPacket->operationId;     
    *q++ = msgPacket->argumentLength;     
    char *p = (char *) q;
    for (int i = 0; i < msgPacket->argumentLength; ++i) {
        *p = msgPacket->arguments[i];
        p++;
    }
}

void print_bytes(char *bytes, unsigned a, unsigned b) {
    int j = 0, count = 0;
    printf("\n%04d:   ", ++count);
    for (unsigned i = a; i < b; ++i) {
        printf("%02x ", (unsigned char) bytes[i]);
        if (++j == 16) {
            printf("\n%04d: ", ++count);
            j = 0;
        }
        if (j % 4 == 0) {
            printf("\t");
        }
    }
    std::cout << std::endl;
}

template<typename T>
std::vector<double> linspace(T start_in, T end_in, int num_in) {
    std::vector<double> linspaced;
    double start = static_cast<double>(start_in);
    double end = static_cast<double>(end_in);
    double num = static_cast<double>(num_in);
    if (num == 0) { return linspaced; }
    if (num == 1) {
        linspaced.push_back(start);
        return linspaced;
    }
    double delta = (end - start) / (num - 1);
    for (int i = 0; i < num-1; ++i) {
          linspaced.push_back(start + delta * i);
    }
    linspaced.push_back(end); // I want to ensure that start and end
                            // are exactly the same as the input
    return linspaced;
}

double sampling(double x) {
    if (abs(x) < 0.01) return 1.0;
    return sin(x) / x;
}

// T = 64, A = 16, d = 32
double fourier_coeff(double t, unsigned n) {
    double p = (32 / (M_PI * n)) * sampling(M_PI * n / 2) - 1;
    double q = sin((M_PI * n / 32) * t);
    return p*q;
}

// // T = 64, A = 16, d = 32
// float fourier_coeff(float t, unsigned n) {
//     return (64 / M_PI) * sin((M_PI * t / 32)*(2*n - 1));
// }

double fourier_sum(double t, unsigned n) {
    double acc = 0;
    for (unsigned i = 1; i <= n; ++i)
        acc += fourier_coeff(t, i);
    return acc;
}

void print_args(float *args) {
    for (int i = 0; i < 512; ++i) 
        printf("%f, %f\n", args[i], args[i + 512]);
}

void send_points(Message &m, DatagramSocket &s) { 
    char bytes[MESSAGE_LENGTH];
    serialize(&m, bytes);
    DatagramPacket p(bytes, MESSAGE_LENGTH, "127.0.0.1", PORT);
    s.send(p);
    cout << "Message sent: \n";
    cout << m << endl;
    cout << "Bytes sent: \n";
    print_bytes(bytes, 0, 32);
}

int receive_ack(DatagramSocket &s) {
    char msg_serialized[MESSAGE_LENGTH];
    DatagramPacket response(msg_serialized, MESSAGE_LENGTH);
    if (s.receive(response) == -1) {
        cout << "[!] Error with ack\n";
        return -1;
    }
    cout << "\nMessage received: \n";
    print_bytes(msg_serialized, 0, 32);
    ByteBuffer bb(msg_serialized, MESSAGE_LENGTH);

    // for some reason you MUST store the values in int variables and contruct the instance with them
    int messageType = bb.readInt();
    int requestId = bb.readInt();
    int operationId = bb.readInt();
    int argumentLength = bb.readInt();
    Message resp((MessageType) messageType, requestId, (OperationId) operationId, argumentLength, (char *) NULL);
    return requestId;
}

int main(int argc, char const *argv[]) {
    int x_len = 512, period = 64, send_count = 10, n = 1, ack = 1;
    float src[1024]; // buffer, 4096 = 1024*sizeof(float)
    vector<double> x_lin = linspace(-(period >> 1), period + (period >> 1), 512);
    fill(src + x_len, src + x_len + x_len, 0); 
    for (unsigned i = 0; i < x_lin.size(); ++i) src[i] = (float) x_lin[i];

    DatagramSocket s;
    s.setTimeout(10, 0);
    for (;n <= send_count; ++n) {
        for (int j = 0; j < x_len; ++j) src[j + x_len] += fourier_coeff(src[j], n);
        Message m (MessageType::REQUEST, ack, OperationId::PLOT, sizeof(src), (char *) src);
        send_points(m, s);
        ack = receive_ack(s);
        if (ack == -1) break;
        printf("Ack %d\n", ack);
    }
    return 0;
}
