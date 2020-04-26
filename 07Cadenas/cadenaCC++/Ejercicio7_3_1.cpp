#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>



using namespace std;

int NumPalabras(char *cadena) {
	int cont=0;
	
 
	for (int i = 0; i < strlen(cadena); i = i+4)
	{
		if (cadena[i] == 'I')
			if(cadena[i+1] == 'P')
				if(cadena[i+2] == 'N')
					cont++;
	}

	return cont;
}



int main()
{
	unsigned t0, t1;
	double tiempo;
	t0=clock();

	double n = rand();
	//n=2;
	n = 100000;
	int p = 0, i;
	char *cadenota = NULL;

	srand (time(NULL));

	
	for (i = 1; i <= n; ++i)
	{
		cadenota = (char*)realloc(cadenota, 4 * i * sizeof(char));	//reserva un espacio de 4 elementos, tres letras y un espacio

		cadenota[p] = 65 + rand() % (90+1 - 65);			//ocupamos limite de 65 a 90 para ubicar la letras solo mayusculas en ascci
		cadenota[p+1] = 65 + rand() % (90+1 - 65);
		cadenota[p+2] = 65 + rand() % (90+1 - 65);
		cadenota[p+3] = ' ';
		p += 4;												//aumenta al indice p 4
	}

	// cout << cadenota << endl;
	cout << NumPalabras(cadenota) << endl;




	t1 = clock();
	tiempo = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
	cout << "Tiempo de ejecucion: " << tiempo << " milisegundos" << endl;

	return 0;
}
