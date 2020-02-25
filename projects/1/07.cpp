// 7.-Elabore un programa para encontrar los números primos menores al valor N que introduzca el
// usuario, mediante el algoritmo de la Criba de Eratóstenes:
// http://es.wikipedia.org/wiki/Criba_de_Erat%C3%B3stenes
// Use un template vector para almacenar objetos de una clase, cuyos miembros son los números
// enteros y un dato tipo bool, para descartar al objeto en el caso de que no sea primo
// (originalmente todos los elementos del vector tienen un valor true en este dato miembro).


#include <iostream>
#include <vector>

using namespace std;


void criba (vector <bool> &p) {
	p[0] = p[1] = false;
	for (int i = 2; i*i < p.size(); i++){
		if (p[i] == false)
			continue;
		for (int j = 2 * i; j < p.size (); j += i)
			p[j] = false;		
	}

}

int main(int argc, const char *argv[])
{
    int n = 10000;
    vector<bool> v_criba(n, true);
    criba(v_criba);
    for (int i = 2; i < v_criba.size(); ++i) {
        if (v_criba[i]) cout << i << ", ";
    }
    cout << endl;
    return 0;
}
