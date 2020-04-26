
// Pruebe el paso por referencia de una variable local atómica hacia los dos hilos y observe
// que no provoca condiciones de competencia.

#include <iostream>
#include <thread>
#include <atomic>

#include <unistd.h>
#include <stdio.h>

using namespace std;

atomic<int> count(0);

void increment(const int &n, atomic<int> &count) {
    // count += n;
    for (int i = 0; i < n; ++i) ++count;
    sleep(1);
}

void decrement(const int &n, atomic<int> &count) {
    // count -= n;
    for (int i = 0; i < n; ++i) --count;
    sleep(1);
}

int main() {
    int n = 99999;
    atomic<int> count(0);
    thread th1(increment, n, ref(count)), th2(decrement, n, ref(count));
    cout << "Proceso principal espera que los hilos terminen\n";
    th1.join();
    th2.join();
    cout << "El hilo principal termina\n";
    cout << count;
    cout << endl;
    exit(0);
}
