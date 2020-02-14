
#ifndef COORDENADA_H
#define COORDENADA_H

#include <iostream>
using namespace std;

class Coordenada {
private:
    double x;
    double y;

    static int count;
public:
    Coordenada (double = 0, double = 0);
    double obtenerX ();
    double obtenerY ();
    friend ostream & operator << (ostream &, const Coordenada &);
    static int get_count() { return count; }
};



#endif