#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;



int NumPalabras(string &cadena) {
	int cont=0;
 
	for (int i = 0; i < cadena.length(); i = i+4)
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


	string str;
	
	
	
	
	int n=100000;
	char a,b,c;

	srand (time(NULL));
	
	for (int i = 0; i < n; ++i)
	{
		a = 65 + rand() % (90+1 - 65);
		b = 65 + rand() % (90+1 - 65);
		c = 65 + rand() % (90+1 - 65);
		str = str + a + b + c + " ";
	}

	// cout << str << endl;
	cout << NumPalabras(str) << endl;

	t1 = clock();
	tiempo = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
	cout << "Tiempo de ejecucion: " << tiempo << " miliseconds" << endl;

	return 0;
}
