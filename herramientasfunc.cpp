#include <iostream>
#include <cstdio>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;
const int N=15000;
long int TIME=10000;
int P=100; //la probabilidad de fragmentacion es 1/P
//DECLARACION DE TODAS LAS FUNCIONES
void inicializarfuerzas(int *);
void vectorfuerza(int V[],int *);
void Desfragmentar(int *,int, int);
void Union (int *,int,int);
void Sacardatos(int *,int V[]);

///////////////////////////////////////////
int main()
{
srand(time(NULL));
int Vect[2*N] /*= {1,1,2,1,3,1,4,1,5,1}*/,Force[N]={0};
inicializarfuerzas(Vect);

for(int time=0;time<TIME;time++)
{
	vectorfuerza(Vect,Force);
	for(int i=0;i<N;i++)  //****PRINTF DE RECTIFICACION
		{
		//	printf(" Elemento [%d] = %d \n",i,Force[i]);
		}	

	int unit =rand()%N; //NUMERO ENTRE 0 Y N-1
	int elegida = Force[unit]; //LA UNIDAD ELEGIDA
	//printf("Unit FUERA IF = %d ... %d \n",elegida,unit); //****PRINTF DE RECTIFICACION

	int frag = rand()%P,count=0; //RODANDO PARA VER SI SE VA A DESFRAGMENTAR O NO
		if(frag==0) // DEBO CAMBIARLO A DIFERENTE
		{
			Desfragmentar(Vect,elegida,count);	//PASAMOS POR REFERENCIA PARA REDISTRIBUIR
		}
		else //SI SE VA A UNIR
		{
			int elegida2=0;
			int unit2 =rand()%N;
			elegida2 = Force[unit2];
			//printf("Unit = %d ... %d \n",elegida2,unit2);
			//SI NO QUEREMOS QUE SE UNA UNIDAD CON ELLA MISMA COLOCAMOS DO-WHILE
			Union(Vect,elegida,elegida2);
		}
}	
		for(int i=0;i<N;i++) //IMPRIME VALOR DE LA FUERZA Y EN QUE UNIDAD //****PRINTF DE RECTIFICACION
		{
			printf(" Unidad [%d] \t Fuerza [%d] \n",Vect[2*i],Vect[2*i+1]);
		}
	int Data[N]={0};
	Sacardatos(Data,Vect);
	for(int i=0;i<N;i++) //IMPRIME DATOS FINALES DE NUMERO DE UNIDADES CON CIERTA FUERZA OMITIENDO LOS QUE NO TIENEN UNIDADES
		{
			if(Data[i]!=0)
			{
			printf(" n_s = %d ******** s= %d  \n",Data[i],i);
			}
		}
return 0;
}

///////////////////////////////////////////////////////
void inicializarfuerzas(int Vect[])
{
	for (int i=0;i<N;i++)
	{
	Vect[2*i+1] = 1;
	Vect[2*i]=i+1;
	}
	
}
/////////////////////////////////////////////////////
void vectorfuerza(int Vect[],int Force[])
{
int contador=0;
for(int i=0;i<N;++i)
	{
		int f=Vect[2*i+1];
		if(f!=0)
		{
			do
			{
			contador=contador+1;
			//printf("CONTADOR = %d \n",contador);
			Force[contador-1]=i+1;
			}
			while(contador<f);
		}
			
	}
	
}
///////////////////////////////////////////////////////

void Desfragmentar(int Vect[], int elegida, int count)
{
int i=0;
			if(Vect[2*elegida-1]!=1) //Evitando crear mas fuerza
			{
				while(count<Vect[2*elegida-1])
				{
					if(Vect[2*i+1]==0) //Vamos a tomar cada uno de los espacios de fuerza vacios 
									//y llenarlos hasta redistribuir la fuerza
					{
				
						Vect[2*i+1]	=1; 
						count=count+1;
					}
					i=i+1;	
				}
			
			Vect[2*elegida-1] =1;//Tome la unidad elegida y set 1.	
			}		 				
	
}
////////////////////////////////////////////////////////

void Union (int Vect[],int elegida, int elegida2)

{
	if(elegida2!=elegida)
	{
	Vect[2*elegida-1] = Vect[2*elegida -1]+Vect[2*elegida2 -1]; //UNIR FUERZAS
	Vect[2*elegida2-1] = 0; //DESAPARECER GRUPO2
	}
}

void Sacardatos(int Data [], int Vect[])
{
	//CADA ENTRADA DE DATA SERA EL NUMERO DE UNIDADES CON ESA FUERZA.
	for (int i=0;i<N;i++)
	{
		int k=Vect[2*i+1];
		Data[k]=Data[k]+1;
	}
}
//////////////////////////////////////////////////////////





