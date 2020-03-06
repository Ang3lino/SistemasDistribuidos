
#ifndef COORDENADA_H
#define COORDENADA_H

#include <iostream>
#include <cmath>

using namespace std;

struct Coordenada {
    double x, y;

    Coordenada (double = 0, double = 0);
    double obtenerX ();
    double obtenerY ();
    double magnitude();

    friend ostream & operator << (ostream &, const Coordenada &);
};

#endif
