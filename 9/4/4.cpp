#include "library.h"
#include <thread>

void uno() {
    thread t1(dd, "output.txt"), t2(dd, "otro.txt");
    t1.join();
    t2.join();
}

void dos() {
    thread t1(ram), t2(ram);
    t1.join();
    t2.join();
}

void tres() {
    thread t1(cpu), t2(cpu);
    t1.join();
    t2.join();
}

void cuatro() {
    thread t1(dd, "salida.txt"), t2(cpu);
    t1.join();
    t2.join();
}

void cinco() {
    thread t1(dd, "salida.txt"), t2(ram);
    t1.join();
    t2.join();
}

void seis() {
    thread t1(cpu), t2(ram);
    t1.join();
    t2.join();
}

void siete() {
    thread t1(cpu), t2(dd, "salida.txt"), t3(ram);
    t1.join();
    t2.join();
    t3.join();
}

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]);
    cout << n << endl;;
    switch (n) {
        case 1: uno();	break;
        case 2: dos();	break;
        case 3: tres();	break;
        case 4: cuatro();	break;
        case 5: cinco();	break;
        case 6: seis();	break;
        case 7: siete();	break;
        default: cout << "Opcion invalida\n";            
    }
    cout << endl;
    return 0;
}
