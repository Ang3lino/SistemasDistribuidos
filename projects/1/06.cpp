// 6.- Utilice composición para elaborar una clase Ortoedro la cual se compone de 6 objetos
// Rectangulo, y donde cada objeto Coordenada es de tres dimensiones. Se debe disponer de los
// metodos: obtieneVertices, obtieneArea y obtieneVolumen para el área de la superficie y el volumen.
// La inicialización del objeto se debe dar mediante las 2 coordenadas de los vértices opuestos donde
// el primer vértice está cerca del origen y el segundo lejos, dentro ambos del primer octante.

#include <set>
#include <cmath>
#include <vector>
#include <iostream>


using namespace std;

class Coordenada {
private:
    double x, y, z;
public:
    Coordenada(double xx=0, double yy=0, double zz=0): x(xx), y(yy), z(zz) {}

    inline double obtenerX() { return x; }
    inline double obtenerY() { return y; }
    inline double obtenerZ() { return z; }
};
// --------------------------------------------------------------------------------------------------

class Rectangulo {  
private:
    Coordenada cercaOrigen, lejosOrigen;

public:
    Rectangulo() {}

    Rectangulo(Coordenada co, Coordenada lo) : cercaOrigen(co), lejosOrigen(lo) {}

    void imprimeEsq() { 
        cout << "Para la esquina superior izquierda.\n";

        cout << "(" << cercaOrigen.obtenerX() << ", ";
        cout << cercaOrigen.obtenerY() << ", ";
        cout << cercaOrigen.obtenerZ() << ")" << endl;

        cout << "(" << lejosOrigen.obtenerX() << ", ";
        cout << lejosOrigen.obtenerY() << ", ";
        cout << lejosOrigen.obtenerZ() << ")" << endl;
    }

    inline vector<Coordenada> esquinas() { return {cercaOrigen, lejosOrigen}; }

    double obtieneArea() { 
        const double a = abs(lejosOrigen.obtenerX() - cercaOrigen.obtenerX());
        const double b = abs(lejosOrigen.obtenerY() - cercaOrigen.obtenerY());
        const double c = abs(lejosOrigen.obtenerZ() - cercaOrigen.obtenerZ());
        return a*b + a*c + b*c;
    }
};


// ----------------------------------------------------------------------------------------------------
class Ortoedro {
private:
    vector<Rectangulo> rectangulos;

public:
    Ortoedro();

    Ortoedro(Coordenada co, Coordenada lo) {
        rectangulos.resize(6);
        const double coX = co.obtenerX();
        const double coY = co.obtenerY();
        const double coZ = co.obtenerZ();
        const double loX = lo.obtenerX();
        const double loY = lo.obtenerY();
        const double loZ = lo.obtenerZ();
        rectangulos[0] = Rectangulo(Coordenada(coX, coY, coZ), Coordenada(loX, coY, loZ)); // frente
        rectangulos[1] = Rectangulo(Coordenada(coX, loY, coZ), Coordenada(loX, loY, loZ)); // derecha
        rectangulos[2] = Rectangulo(Coordenada(coX, coY, coZ), Coordenada(coX, loY, loZ)); // atras
        rectangulos[3] = Rectangulo(Coordenada(loX, coY, coZ), Coordenada(loX, loY, loZ)); // izquierda
        rectangulos[4] = Rectangulo(Coordenada(coX, coY, loZ), Coordenada(loX, loY, loZ)); // arriba
        rectangulos[5] = Rectangulo(Coordenada(coX, coY, coZ), Coordenada(loX, loY, coZ)); // abajo
    }

    vector<Coordenada> obtieneVertices() {
        auto cmp = [](Coordenada a, Coordenada b) {
            if (a.obtenerX() < b.obtenerX()) return true;
            if (a.obtenerX() > b.obtenerX()) return false;
            if (a.obtenerY() < b.obtenerY()) return true;
            if (a.obtenerY() > b.obtenerY()) return false;
            if (a.obtenerZ() < b.obtenerZ()) return true;
            return false;
        };
        set<Coordenada, decltype(cmp)> s(cmp);
        for (auto &rec : rectangulos) {
            for (auto &esq : rec.esquinas()) {
              s.insert(esq);
            }
        }
        vector<Coordenada> ans;
        ans.insert(ans.end(), s.begin(), s.end());
        return ans;
    }

    double obtieneArea() {
        double ans = 0;
        for (auto &rec : rectangulos) {
            ans += rec.obtieneArea();
        }
        return ans;
    }

    double obtieneVolumen() {
        double bottomArea = rectangulos[5].obtieneArea();
        vector<Coordenada> esquinas = rectangulos[0].esquinas();
        return bottomArea * (abs(esquinas[1].obtenerZ() - esquinas[0].obtenerZ()));
    }
};


// ----------------------------------------------------------------------------------------------------
int main() {
    double a, b, c, d, e, f;
    cout << "Tres coordenadas de la esquina cerca del origen: ";
    cin >> a >> b >> c;
    cout << "Tres coordenadas de la esquina lejos del origen: ";
    cin >> d >> e >> f;
    Ortoedro o(Coordenada(a, b, c), Coordenada(d, e, f));
    cout << "Vertices:" << endl;
    for (Coordenada v : o.obtieneVertices()) {
        cout << "(" << v.obtenerX() << ", " << v.obtenerY() << ", " << v.obtenerZ() << ")" << endl;
    }
    cout << "Area: " << o.obtieneArea() << endl;
    cout << "Volumen: " << o.obtieneVolumen() << endl;
    return 0;
}

