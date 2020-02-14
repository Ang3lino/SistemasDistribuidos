
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

vector<PoligonoIrreg> test(const bool reserve, const int n, const int m) {
    vector<PoligonoIrreg> pols;
    if (reserve) {
        pols.reserve(n);
    }
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        PoligonoIrreg p;
        if (reserve) p.resize(m);
        for (int j = 0; j < m; ++j) {
            Coordenada c(rand() % 100, rand() % 100);
            (reserve) ? p.setVertice(c, j) : p.anadeVertice(c);
        }
        if (reserve) pols[i] = p;
        else pols.push_back(p);
    }
    return pols;
}

int main(int argc, char const *argv[]) {
    int pols_count = 2, coordinates_count = 3;
    bool reserve = true;
    if (argc == 4) {
        pols_count = atoi(argv[1]);
        coordinates_count = atoi(argv[2]);
        if (argv[3] == "n") reserve = false;
    } else {
        cout << "[%s] [N_POLIGONE] [N_COORDINATE] [RESERVE]" << endl;
    }
    auto irreg_pols = test(reserve, pols_count, coordinates_count);
    cout << irreg_pols.size() << endl;

    // int i = 0;
    // for (auto &p: irreg_pols) {
    //     cout << i << endl;
    //     p.imprimeVertices();
    //     ++i;
    //     cout << endl;
    // }

    cout << "Numero de vertices totales: " << Coordenada::get_count() << endl;
    return 0;
}
