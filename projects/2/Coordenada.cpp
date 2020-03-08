
#include "Coordenada.h"


Coordenada::Coordenada (double xx, double yy):x (xx), y (yy) {

}

ostream& operator << (ostream &out, const Coordenada &c) {
    out << "(";
    out << c.x;
    out << ", ";
    out << c.y;
    out << ")";
    return out;
}

double Coordenada::magnitude() {
    return sqrt(x*x + y*y);
}

void Coordenada::move(const double dx, const double dy) {
    x += dx;
    y += dy;
}

//
void Coordenada::rotate(const double theta) {
    const double a = x, b = y;
    const double c = cos(theta), s = sin(theta);
    x = a*c - b*s;
    y = a*s + b*c;
}
