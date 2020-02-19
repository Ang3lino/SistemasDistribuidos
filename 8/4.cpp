
// Modifique el ejercicio anterior para que uno de los hilos decremente n veces la variable
// global y en el otro hilo se incremente n veces la variable global. Cuando ambos hilos terminen
// imprima el valor de la variable en el programa principal que debería ser cero. Incremente el valor
// de n hasta que se produzcan inconsistencias debidas a las condiciones de competencia.

#include <iostream>
#include <thread>
#include <atomic>

#include <unistd.h>
#include <stdio.h>

using namespace std;

int count = 0;

void increment(const int n) {
    // count += n;
    for (int i = 0; i < n; ++i) ++count;
    sleep(1);
}

void decrement(const int n) {
    // count -= n;
    for (int i = 0; i < n; ++i) --count;
    sleep(1);
}

int main() {
    // int n = 999999999;
    int n = 99999;
    thread th1(increment, n), th2(decrement, n);
    cout << "Proceso principal espera que los hilos terminen\n";
    th1.join();
    th2.join();
    cout << "El hilo principal termina\n";
    cout << count;
    cout << endl;
    exit(0);
}