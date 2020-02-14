
#include <time.h>
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <random>

#include "Coordenada.h"
#include "PoligonoIrreg.cpp"


int main(int argc, char const *argv[]) {
    const int n = 10;
    vector<Coordenada> coordinates(n);
    srand(time(NULL));
    const int lim = 200;
    for (int i = 0; i < n; ++i) {
        const int x = (rand() % lim) - 100, y = (rand() % lim) - 100;
        coordinates[i] = Coordenada(x, y);
    }
    for (auto it = coordinates.begin(); it < coordinates.end(); ++it) {
        cout << *it;
    }
    sort(coordinates.begin(), coordinates.end(), [](Coordenada &l, Coordenada &r) {
            return l.magnitude() < r.magnitude();
        }
    );
    cout << "Ordenado " << endl;
    for (auto it: coordinates) {
        cout << it;
    }
    return 0;
}
