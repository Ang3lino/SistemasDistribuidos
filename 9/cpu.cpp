
#include <iostream>
#include <cmath>
using namespace std;

int main() {
	const double MAX = 1e8;

	double seno = 0;
	double coseno = 0;
	double tangente = 0;
	double logaritmo = 0;
	double raizCuadrada = 0;

	for (double i = 1; i < MAX; ++i) {
		seno += sin(i);
		coseno += cos(i);
		tangente += tan(i);
		logaritmo += log(i);
		raizCuadrada += sqrt(i);
	}

	return 0;
}