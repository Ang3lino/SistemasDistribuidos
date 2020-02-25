// 2.- Escriba un programa que imprima la altura de un edificio, si se conoce el tiempo que tardó una
// pelota de tenis desde que se dejó caer en la parte más alta del edificio y hasta llegar al piso.
#include <iostream>
#define GRAVITY 9.807
using namespace std;


inline double height(double t) {
	return 0.5 * GRAVITY * t * t;
}

int main() {
    double t;
    cout << "tiempo: ";
    cin >> t;
    cout << "altura: " << height(t) << endl;
    return 0;
}
