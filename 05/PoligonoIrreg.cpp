
#include "Coordenada.h"
#include <vector>    

struct PoligonoIrreg {
    vector<Coordenada> coordenadas;

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
        for (auto c: coordenadas) 
            cout << c;
            // cout << c.obtenerX() << ", " << c.obtenerY() << endl;
    }
};