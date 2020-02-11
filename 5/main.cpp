
#include <time.h>
#include <stdlib.h>

#include "Coordenada.h"
#include "PoligonoIrreg.cpp"

void ejercicio2() {
    double one = 1;
    Coordenada c(one, one);
    PoligonoIrreg p;
    p.anadeVertice(c);
    p.anadeVertice(c);
    p.imprimeVertices();
}

void test(const bool reserve, const int n, const int m) {
    vector<PoligonoIrreg> pols;
    if (reserve) pols.reserve(n);
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        PoligonoIrreg p;
        if (reserve) p.reserve(m);
        for (int j = 0; j < m; ++j) {
            Coordenada c(rand() % 100, rand() % 100);
            (reserve) ? p.setVertice(c, j) : p.anadeVertice(c);
        }
        if (reserve) pols[i] = p;
        else pols.push_back(p);
    }
}

int main(int argc, char const *argv[]) {
    int pols_count = 3, coordinates_count = 3;
    bool reserve = false;
    if (argc == 4) {
        pols_count = atoi(argv[1]);
        coordinates_count = atoi(argv[2]);
        if (argv[3] == "n") reserve = false;
    } else {
        cout << "[%s] [N_POLIGONE] [N_COORDINATE] [RESERVE]" << endl;
    }
    test(reserve, pols_count, coordinates_count);
    return 0;
}
