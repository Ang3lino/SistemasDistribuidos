
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

inline bool time_ok(int src, int low, int high, string desc) {
    if (src < low || src > high) {
        cout << desc + " invalido." << endl;
        exit(EXIT_FAILURE);
    }
}

class Fecha {
private:
    int dia, mes, anio;


public:
    Fecha(int dd, int mm, int aaaa): dia(dd), mes(mm), anio(aaaa) {
        time_ok(dd, 1, 30, "dia");
        time_ok(mm, 1, 12, "mes");
        time_ok(mm, 0, 2020, "anio");
    }

    Fecha() { }

    /* La función devuelve 1 si fecha1 > fecha2, 0 si son iguales y -1 si fecha1 < fecha2. 
     */
    static int cmp(const Fecha f1, const Fecha f2) {
        if (f1.anio > f2.anio) return 1; 
        if (f1.anio == f2.anio) {
            if (f1.mes > f2.mes) return 1;
            if (f1.mes == f2.mes) { 
                if (f1.dia > f2.dia) return 1; 
                if (f1.dia == f2.dia) return 0;
            }
        }
        return -1;
    }

    // La función devuelve 1 si fecha1 > fecha2, 0 si son iguales y -1 si fecha1 < fecha2. 
    static int cmp_ref(const Fecha &f1, const Fecha &f2) {
        if (f1.anio > f2.anio) return 1; 
        if (f1.anio == f2.anio) {
            if (f1.mes > f2.mes) return 1;
            if (f1.mes == f2.mes) { 
                if (f1.dia > f2.dia) return 1; 
                if (f1.dia == f2.dia) return 0;
            }
        }
        return -1;
    }

};

void measure_time(void (*fun)(bool), bool ref) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    fun(ref);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "Time difference = " << diff << "[µs]" << std::endl;
}

void compare_n(bool ref=true) {
    Fecha a(24, 8, 1998), b(24, 8, 1997);
    const int n = 1e7;
    if (ref) {
        for (int i = 0; i < n; ++i) Fecha::cmp_ref(a, b);
    } else {
        for (int i = 0; i < n; ++i) Fecha::cmp(a, b);
    }
}

int main(void) {
    measure_time(compare_n, false);
    measure_time(compare_n, true);
    return 0;
}

