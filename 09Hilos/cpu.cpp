
#include <iostream>
#include <cmath>
using namespace std;

void cpu() {
	const double MAX = 105000000;
	double seno = 0, coseno = 0, tangente = 0, logaritmo = 0, raizCuadrada = 0;
	for (double i = 1; i < MAX; ++i) {
		seno += sin(i);
		coseno += cos(i);
		tangente += tan(i);
		logaritmo += log(i);
		raizCuadrada += sqrt(i);
	}
}

int main() {
    cpu();
    return 0;
}
