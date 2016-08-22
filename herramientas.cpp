#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
const int N=10;

int main()

{
int Vect[2*N] = {0};
//debe haber un for para el time
for (int i=0;i<=N;i++) //TRATAR DE INICIALIZAR FUERZAS
	{
	Vect[2*i-1] = 1;
	}
	
	for(int i=0;i<2*N;i++)
	{
	printf("Entrada %d \t Contenido %d \n",i+1,Vect[i]);
	}
return 0;
}
