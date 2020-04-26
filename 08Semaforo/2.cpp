
// Cree una variable entera global (fuera de main) con valor inicial de cero. Haga una
// función para que uno de los hilos incremente la variable una unidad y después se duerma un
// segundo y otra función para que otro hilo la decremente en una unidad y después se duerma un
// segundo. Al final, cuando terminen de ejecutarse los dos hilos, imprima el valor de dicha variable
// global en el hilo principal. ¿Los hilos comparten la variable? 

#include <iostream>
#include <unistd.h>
#include <thread>

#include <stdio.h>

using namespace std;

int count = 0;

void increment() {
    ++count;
    sleep(1);
}

void decrement() {
    --count;
    sleep(1);
}

int main() {
    thread th1(increment), th2(decrement);
    cout << "Proceso principal espera que los hilos terminen\n";
    th1.join();
    th2.join();
    cout << "El hilo principal termina\n";
    cout << count;
    cout << endl;
    exit(0);
}