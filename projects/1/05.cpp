// 5.- Defina una clase llamada Fraccion , la cual almacena un numerador y un denominador enteros.
// Debe incluir una función para que el usuario pueda inicializar a ambos, así como una función que
// devuelva el resultado de la división entre el numerador y el denominador como un double. Por último
// debe existir una función que devuelva a la fracción en su mínima expresión. Por ejemplo la fracción
// 18/15 deberá imprimirse como 6/5. Pruebe la clase con el código mínimo en el programa principal.
#include <iostream>
#include <algorithm>

using namespace std;

class Fraccion {
private:
    long num, den;

    void simplify() {
        const long gcd = __gcd(num, den);
        num /= gcd;
        den /= gcd;
    }

public:
    void update(long num, long den) {
        this->num = num;
        this->den = den;
        simplify();
    }

    Fraccion(long num_, long den_): num(num_), den(den_) {  
        simplify();
    }

    double as_double() { return (double) num / den; }

    friend ostream& operator<<(ostream& os, const Fraccion&);
};

ostream& operator<<(ostream& os, const Fraccion &f) {
    os << f.num << "/" << f.den << endl;
    return os;
}

// ----------------------------------------------------------
int main(int argc, const char *argv[]) {
    Fraccion f(10000, 5000);
    cout << f << endl;
    f.update(18, 15);
    cout << f << endl;
    return 0;
}
