
#ifndef COORDENADA_H
#define COORDENADA_H

#include <iostream>
using namespace std;

class Coordenada {
private:
    double x;
    double y;
public:
    Coordenada (double = 0, double = 0);
    double obtenerX ();
    double obtenerY ();
    friend ostream & operator << (ostream &, const Coordenada &);
};

#endif