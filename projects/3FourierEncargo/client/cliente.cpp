#include "Solicitud.h"

#include <iostream>
#include <vector>

#include <cstring>
#include <string>
#define _USE_MATH_DEFINES  // use M_PI
#include <cmath>

using namespace std;


const int puerto = 7200;
const int periodo = 64;
const int L = periodo / 2;

char *ip = "127.0.0.1";


vector<double> linspace(double min, double max, double points) {
    vector<double> d;
    d.resize(points);
    for (int i = 0; i < points; i++) {  
        d[i] = ( min + i * (max - min) / (points - 1) ); 
    }  
    return d;  
}

double coeficiente_fourier(double x, unsigned n) {
    const double cte = -4*L / (M_PI * M_PI);
    return cte * cos((2*n + 1)*M_PI*x / L) / ((2*n + 1)*(2*n + 1));
}

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
    int n;  
    Solicitud solicitud;

    // inicia los vectores discretos x, y
    iniciar_x(x, cantidad_muestras);
    fill_n(y, cantidad_muestras, L/2); 

    solicitud.doOperation(ip, puerto, ENVIAR_X, (char *) &x[0]);
    for (n = 0; ; ++n) {
        for (int i = 0; i < cantidad_muestras; ++i) y[i] += coeficiente_fourier(x[i], n); 
        solicitud.doOperation(ip, puerto, ENVIAR_Y, (char *) &y[0]);
    }
    return 0;
}
