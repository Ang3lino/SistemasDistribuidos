// 3.- Escriba un programa que reciba del usuario un valor entero de tiempo en segundos, y que
// imprima su equivalente en horas, minutos y segundos. Por ejemplo si el usuario introduce 50381,
// entonces el programa debe imprimir: 13 horas, 59 minutos y 41 segundos.
#include <iostream>
using namespace std;


int main( ) {
    long time = 0;
    cin >> time;
    const int hours = time / 3600 % 60;
    const int minutes = time / 60 % 60;
    const int seconds = time % 60;
    cout << "Time: " << hours << ":" << minutes << ":" << seconds << endl;
    return 0;
}
