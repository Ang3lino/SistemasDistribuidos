
#include <cmath>

int main(int argc, char const *argv[])
{
    double seno = 0, coseno = 0, tangente = 0;
    double logaritmo =0, raizCuad = 0;
    const double max = 10e7;
    for (double i = 1; i < max; ++i) {
        seno += sin(i);
        coseno += cos(i);
        tangente += tan(i);
        logaritmo += log(i);
        raizCuad += sqrt(i);
    }
    return 0;
}
