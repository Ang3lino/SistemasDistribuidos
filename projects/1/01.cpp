// 1.-Se desea calcular la raíz cuadrada de un número entero n utilizando al algoritmo babilónico.
// Investigue en Internet el algoritmo y prográmelo, haciendo n del tipo double y el resultado con
// cuatro decimales.
#include <iostream>

using namespace std;


double sqrt_babylonian(double n) {
	double x0 = 0, x1 = 0.5;
	while(abs(x0 - x1) >= 1e-6) {
		x0 = x1;
		x1 = 0.5 * (x0 + n / x0);
	}
	return x1;
}

int main() {
    int n = 100;
    cout << sqrt_babylonian(n) << endl;
    return 0;
}
