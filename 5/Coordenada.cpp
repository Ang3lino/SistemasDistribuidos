#include "Coordenada.h"

int Coordenada::count = 0;

Coordenada::Coordenada (double xx, double yy):x (xx), y (yy) {
  count++;
}

ostream& operator << (ostream &out, const Coordenada &c) {
    out << "(";
    out << c.x;
    out << ", ";
    out << c.y;
    out << ")\n";
    return out;
}

double Coordenada::obtenerX () {
  return x;
}

double Coordenada::obtenerY () {
  return y;
}

