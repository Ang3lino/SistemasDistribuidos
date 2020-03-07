
#include "Ellipse.h"


Ellipse::Ellipse(const int a_, const int b_): a(a_), b(b_ ) {
}

void Ellipse::set_contour(const int resolution) {
    vector<double> x_values = linspace<double>(-a, a, samples);
    IrregularPolygon ip(samples);
    transform(x_values.begin(), x_values.end(), ip.coordinates.begin(), [&](double x_i) {
        return Coordenada(x_i, ellipse(x_i, a, b)); 
    });
    unsigned i = ip.coordinates.size();
    while (i--) {
        const Coordenada c = ip.coordinates[i];
        ip.coordinates.emplace_back(c.x, -c.y);
    }
    return ip;
}


void Ellipse::move(const int dx, const int dy) {
    transform(coordinates.begin(), coordinates.end(), coordinates.begin(), 
        [&](Coordenada c) {
            c.x += dx;
            c.y += dy;
            return c;
    });
}

ostream & operator << (ostream &out, Ellipse &ellipse) {
    out << "(h, k) = " << "( " << ellipse.h << ", " << ellipse.k << ")" << endl;
    out << "a = " << ellipse.a << endl;
    out << "b = " << ellipse.b << endl;
    for (auto &c: ellipse.coordinates) out << c << endl;
    return out;
}

inline double ellipse(const double x, const double a, const double b) {
    assert (x <= a);
    return b*sqrt(1 - (x/a)*(x/a));
}


