#include <iostream>
using namespace std;

#define numeroElementos 100000000
#define RAM_COUNT 400000000

void ram() {
    int *arreglo, i;
    arreglo = new int[numeroElementos];
    for(i = 0; i < numeroElementos; i++)
        arreglo[i] = 0;
    for(i = 0; i < RAM_COUNT; i++){
        arreglo[rand() % numeroElementos] = rand();
    }
}

int main(){
    ram();
    return 0;
}
