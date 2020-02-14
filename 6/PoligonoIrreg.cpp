
#include "Coordenada.h"
#include <vector>    
#include <iterator>


struct PoligonoIrreg {
    vector<Coordenada> coordenadas;
    static int count;

    PoligonoIrreg() { }


    PoligonoIrreg(const int n) {
        coordenadas.reserve(n);
    }

    void reserve(const int n) {
        coordenadas.reserve(n);
    }

    void resize(const int n) {
        coordenadas.resize(n);
    }

    void anadeVertice(Coordenada &c) {
        coordenadas.push_back(c);
    }

    void setVertice(const Coordenada &c, const int i) {
        coordenadas[i] = c;
    }

    void imprimeVertices() {
        for (auto it = coordenadas.begin(); it < coordenadas.end(); ++it) {
            cout << "Coordenada: " << *it << "  Magnitud: " << it->magnitude() << endl;
        }
    }
};