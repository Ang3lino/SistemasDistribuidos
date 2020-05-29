
#ifndef IRREGULAR_POLYGON
#define IRREGULAR_POLYGON

#include <iterator>
#include <iostream>
#include <vector>    
#include "Coordenada.h"

struct IrregularPolygon {
    vector<Coordenada> coordinates;
    static int count;

    IrregularPolygon();

    IrregularPolygon(const int);

    void reserve(const int);

    void resize(const int);

    void add_vertex(Coordenada);

    void set_vertex(const Coordenada &, const int);

    friend ostream & operator << (ostream &, IrregularPolygon &);
};


#endif
