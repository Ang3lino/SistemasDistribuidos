// 4.- Defina una clase Temperatura que almacene de manera interna un valor de temperatura en
// grados Kelvin. También elabore las funciones setTempKelvin, setTempFahrenheit y setTempCelsius que
// tomen la temperatura en la escala especificada por el usuario y la almacenen en grados Kelvin.
// Asimismo escriba las funciones que impriman el valor almacenado en la clase y en los grados
// Centigrados, Kelvin o Fahrenheit, según lo solicite el usuario. Escriba una función principal para
// probar la clase.
#include <iostream>

using namespace std;


class Temperatura {
    double kelvin;

public:
    inline void setTempKelvin(double kelvin_) { kelvin = kelvin_; } 
    inline void setTempFahrenheit(double fahrenheit) { kelvin = (fahrenheit - 32) / 1.8 + 273.15; }
    inline void setTempCelsius(double celsius) { kelvin = celsius + 273.15; }

    inline double getTempKelvin() { return kelvin; }
    inline double getTempFahrenheit() { return 1.8 * (kelvin - 273.15) + 32; }
    inline double getTempCelsius() { return kelvin - 273.15; }

    Temperatura(): kelvin(0) {  }
};

// ------------------------------------------------------------------------------------------------
int main(int argc, const char *argv[])
{
    Temperatura temperatura;
    temperatura.setTempKelvin(100);
    cout << temperatura.getTempKelvin() << endl;
    temperatura.setTempFahrenheit(100);
    cout << temperatura.getTempFahrenheit() << endl;
    temperatura.setTempCelsius(100);
    cout << temperatura.getTempCelsius() << endl;
    return 0;
}
