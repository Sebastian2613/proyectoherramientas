#include <iostream>
#include <cstdio>
#include <string>
#include <time.h>
using namespace std;
const int N=10;

int main()

{
int Vect[2*N] = {0};
//debe haber un for para el time
for (int i=1;i<=N;i++) //TRATAR DE INICIALIZAR FUERZAS VAMOS A COLOCARLAS EN LAS ENTRADAS IMPARES
	{
	Vect[2*i-1] = 1;
	Vect[2*i]=i;
	}

for(int time=1;time<3;time++)
	{
		//DE ALGUNA MANERA SACAR CAD UNIDAD Y SACAR SU PROBABILIDAD DE SEPARARSE
		for(int unit=1;unit<=N;unit++)
		{
		
		}
	}

	for(int i=0;i<N;i++) //IMPRIME VALOR DE LA FUERZA Y EN QUE UNIDAD
	{
	printf(" Unidad [%d] \t Fuerza [%d] \n",1+Vect[2*i],Vect[2*i+1]);
	}
return 0;
}
