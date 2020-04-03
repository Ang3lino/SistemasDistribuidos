
#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <set>
#include <vector>    
#include <iterator>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <experimental/random>
#include "IrregularPolygon.h"

using namespace std;

// We'll draw an asteroid by using an Ellipse
struct Ellipse: IrregularPolygon {
    int a, b;  // axis, a is supposed to be the big one
    int h, k;  // the center of the ellipse
    int x, y;  // direction
    int rgb[3];
    double omega;  // angle rotation

    Ellipse(const int, const int);  // a, b
    Ellipse(const int, const int, const int, const int);  // a, b, h, k

    void move(const int, const int);
    void set_contour(const int);
    void rotate(const double);  // rotate over the center
    void rotate(const double, const double, const double); // rotate over p.x, p.y
    void scale(const double);

    friend ostream & operator << (ostream &, IrregularPolygon &);
};


#endif
