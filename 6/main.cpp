
#include <time.h>
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <random>

#include "Coordenada.h"
#include "PoligonoIrreg.cpp"

double fixed_precision(const double d) {
    return floor(d * 1000) / 1000;
}

int main(int argc, char const *argv[]) {
    const int n = 10;
    vector<Coordenada> coordinates(n);
    PoligonoIrreg p;
    srand(time(NULL));

    std::random_device rd;
    std::default_random_engine generator(rd()); // rd() provides a random seed
    std::uniform_real_distribution<double> distribution(-100, 100);

    for (int i = 0; i < n; ++i) {
        const double x = fixed_precision(distribution(generator));
        const double y = fixed_precision(distribution(generator));
        coordinates[i] = Coordenada(x, y);
    }
    p.coordenadas = coordinates;
    cout << "Desordenado:\n";
    p.imprimeVertices();
    cout << "\n\n";
    sort(p.coordenadas.begin(), p.coordenadas.end(), [](Coordenada &l, Coordenada &r) {
            return l.magnitude() < r.magnitude();
        }
    );
    cout << "Ordenado " << endl;
    p.imprimeVertices();
    return 0;
}
