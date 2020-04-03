
#ifndef COORDENADA_H
#define COORDENADA_H

#include <iostream>
#include <cmath>

using namespace std;

struct Coordenada {
    double x, y;

    Coordenada (double = 0, double = 0);
    void rotate(const double);
    void move(const double, const double);
    double magnitude();

    friend ostream & operator << (ostream &, const Coordenada &);
};

#endif
