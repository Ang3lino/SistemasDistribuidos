#include "Solicitud.h"

#include <iostream>
#include <vector>

#include <cstring>
#include <string>
#define _USE_MATH_DEFINES  // use M_PI
#include <math.h>


using namespace std;

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
    linspaced.push_back(end); 
    return linspaced;
}

// T = 64, A = 16, d = 32
inline double coeficiente_fourier(double x, unsigned n) {
    return (64 / M_PI) * sin((M_PI * x / 32)*(2*n - 1));
}

int puerto = 7200;
int periodo = 64;
char *ip = "127.0.0.1";


void iniciar_x(double *dst, int n) {
    auto src = linspace(-periodo / 2, periodo + periodo / 2, n);
    copy(src.begin(), src.end(), dst);
}

void mostrar_arreglo(double *arr, int n) {
    cout << "[ " ;
    for (int i = 0; i < n; ++i) {
        cout << arr[i];
        cout << ", ";
    }
    cout << " ]" << endl;
}

int main(int argc, char *argv[]) {
    int cantidad_muestras = TAM_MAX_DATA / 8;
    double x[cantidad_muestras], y[cantidad_muestras];
    int respuesta, n = 0, muestrasPorEnviar = 1;  
    Solicitud solicitud;

    // inicia los vectores discretos x, y
    iniciar_x(x, cantidad_muestras);
    memset(y, 0, sizeof(y));

    solicitud.doOperation(ip, puerto, ENVIAR_X, (char *) &x[0]);
    while (++n <= muestrasPorEnviar) {
        for (int i = 0; i < cantidad_muestras; ++i) y[i] += coeficiente_fourier(x[i], n); 
        solicitud.doOperation(ip, puerto, ENVIAR_Y, (char *) &y[0]);
    }
    mostrar_arreglo(y, cantidad_muestras);

    return 0;
}
