
#include "IrregularPolygon.h"

int IrregularPolygon::count = 0;

IrregularPolygon::IrregularPolygon() { 
    IrregularPolygon::count = IrregularPolygon::count + 1;
}

IrregularPolygon::IrregularPolygon(const int n) {
    coordinates.resize(n);
    ++IrregularPolygon::count;
}

void IrregularPolygon::reserve(const int n) {
    coordinates.reserve(n);
    ++IrregularPolygon::count;
}

void IrregularPolygon::resize(const int n) {
    coordinates.resize(n);
}

void IrregularPolygon::add_vertex(Coordenada c) {
    coordinates.push_back(c);
}

void IrregularPolygon::set_vertex(const Coordenada &c, const int i) {
    coordinates[i] = c;
}

ostream & operator << (ostream &out, IrregularPolygon &ip) {
    unsigned i = 0;
    for (auto c: ip.coordinates) {
        out << "v_" << i << " = " << c << " |v_i| = " << c.magnitude() << endl;
        ++i;
    }
    return out;
}

