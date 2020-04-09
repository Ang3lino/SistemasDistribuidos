#include <iostream>
#include <vector>
#include <algorithm> 

#define _USE_MATH_DEFINES  // use M_PI
#include <math.h>

#include "Message.h"
#include "DatagramSocket.h"
#include "ByteBuffer.h"
#include "Request.h"


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

int main(int argc, char const *argv[]) {
    int x_len = 512, period = 64, send_count = 10, n = 1, ack = 1;
    float src[1024]; // buffer, 4096 = 1024*sizeof(float)
    vector<double> x_lin = linspace(-(period >> 1), period + (period >> 1), 512);
    fill(src + x_len, src + x_len + x_len, 0); 
    for (unsigned i = 0; i < x_lin.size(); ++i) src[i] = (float) x_lin[i];
    string ip = "127.0.0.1";
    Request request(ip, PORT);
    request.setSoTimeout(10, 0);

    for (; ; ++n) {
        for (int j = 0; j < x_len; ++j) src[j + x_len] += fourier_coeff(src[j], n);
        char *response = request.doOperation(OperationId::PLOT, (char *) src, sizeof(src));
    }
    return 0;
}
