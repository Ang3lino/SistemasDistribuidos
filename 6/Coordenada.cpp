#include "Coordenada.h"

Coordenada::Coordenada (double xx, double yy):x (xx), y (yy) {
}

ostream& operator << (ostream &out, const Coordenada &c) {
    out << "(";
    out << c.x;
    out << ", ";
    out << c.y;
    out << ")\n";
    return out;
}

double Coordenada::magnitude() {
  return sqrt(x*x + y*y);
}

double Coordenada::obtenerX () {
  return x;
}

double Coordenada::obtenerY () {
  return y;
}

