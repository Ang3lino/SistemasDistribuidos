
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

int main(int argc, char const *argv[]) {
    int n = 2, m = 3;
    bool reserve = true;

    if (argc == 4) {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
        if (argv[3] == "n") reserve = false;
    } else {
        cout << "[%s] [N_POLIGONE] [N_COORDINATE] [RESERVE]" << endl;
    }


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

    for (auto p: pols) {
        p.imprimeVertices();
    }

    cout << pols.size() << endl;
    cout << "Numero de vertices totales: " << Coordenada::get_count() << endl;

    return 0;
}
