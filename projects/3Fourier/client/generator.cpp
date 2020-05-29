/**
 * Author: Angel Manriquez
 */


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

const int PORT = 5400;
const int N_SAMPLES = ARG_LEN >> 2;


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

// T = 64, A = 8, d = 32
double fourier_coeff(double t, unsigned n) {
    double p = (32 / (M_PI * n)) * sampling(M_PI * n / 2) - 1;
    double q = sin((M_PI * n / 32) * t);
    return p*q;
}

// // T = 64, A = 16, d = 32
// double fourier_coeff(double t, unsigned n) {
//     return (64 / M_PI) * sin((M_PI * t / 32)*(2*n - 1));
// }

double fourier_sum(double t, unsigned n) {
    double acc = 0;
    for (unsigned i = 1; i <= n; ++i)
        acc += fourier_coeff(t, i);
    return acc;
}

void print_args(float *x, float *y) {
    for (int i = 0; i < N_SAMPLES; ++i) 
        printf("%f, %f\n", x[i], y[i]);
}

int main(int argc, char const *argv[]) {
    string ip = "127.0.0.1";
    Request request(ip, PORT);
    request.setSoTimeout(10, 0);

    if (argc == 2) {
        ip = argv[1];
    }

    int period = 64, n = 1;
    float x[N_SAMPLES], y[N_SAMPLES]; // buffer, 4096 = 1024*sizeof(float)
    vector<double> x_lin = linspace(-(period >> 1), period + (period >> 1), N_SAMPLES);
    for (unsigned i = 0; i < N_SAMPLES; ++i) x[i] = (float) x_lin[i];
    request.doOperation(OperationId::SET_X_AXIS, (char *) x, sizeof(x));

    fill(y, y + N_SAMPLES, 0); 
    for (;; ++n) {
        for (int j = 0; j < N_SAMPLES; ++j) y[j] += fourier_coeff(x[j], n);
        // print_args(x, y);
        request.doOperation(OperationId::PLOT, (char *) y, sizeof(y));
    }
    return 0;
}
