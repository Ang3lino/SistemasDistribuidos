
#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <vector>    
#include <iterator>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include "IrregularPolygon.h"

using namespace std;

struct Ellipse: IrregularPolygon {
    int a, b;
    int h, k;

    Ellipse(const int, const int);

    void move(const int, const int);

    friend ostream & operator << (ostream &, IrregularPolygon &);
};


#endif
