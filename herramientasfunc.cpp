#include <iostream>
#include <cstdio>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;
const int N=100000;
long int TIME=3000000;
int P=100; //la probabilidad de fragmentacion es 1/P
//DECLARACION DE TODAS LAS FUNCIONES
void inicializarfuerzas(int *);
void vectorfuerza(int V[],int *);
void Desfragmentar(int *,int, int);
void Union (int *,int,int);
void Sacardatos(int *,int V[]);
double pendiente(int n, double *,double *);

/*ESTA PARTE DEL CÓDIGO FUE SACADA DE OTRO LADO*/
#ifndef MATHS_REGRESSION_LINEAR_H
#define MATHS_REGRESSION_LINEAR_H

#include <assert.h>
#include <math.h>

namespace Maths
{

namespace Regression
{

//! Given a set of points, this class calculates the linear regression parameters and evaluates the regression line at arbitrary abscissas.

class Linear
{
public:

//! Class constructor

Linear(int n, double *x, double *y)
{

            // calculate the averages of arrays x and y
            double xa = 0, ya = 0;
            for (int i = 0; i < n; i++) {
                xa += x[i];
                ya += y[i];
            }
            xa /= n;
            ya /= n;

            // calculate auxiliary sums
            double xx = 0, yy = 0, xy = 0;
            for (int i = 0; i < n; i++) {
                double tmpx = x[i] - xa, tmpy = y[i] - ya;
                xx += tmpx * tmpx;
                yy += tmpy * tmpy;
                xy += tmpx * tmpy;
            }

            // calculate regression line parameters

            // make sure slope is not infinite
           // assert(fabs(xx) != 0);

                m_b = xy / xx;
                m_a = ya - m_b * xa;
            m_coeff = (fabs(yy) == 0) ? 1 : xy / sqrt(xx * yy);

        }

//! Evaluates the linear regression function at the given abscissa.

double getValue(double x)
{
    return m_a + m_b * x;
}

//! Returns the slope of the regression line

double getSlope()
{
   return m_b;
}

//! Returns the intercept on the Y axis of the regression line

double getIntercept()
{
  return m_a;
}

//! Returns the linear regression coefficient

double getCoefficient()
{
  return m_coeff;
}

private:

double m_a, m_b, m_coeff;
};


//! A static function implementing the Linear Class for one off calculations

double Linear_once(int n, double *x, double *y, double a )
{
  // This function is created to enable an Instant Calculator on CodeCogs. 
  // You probably shouldn't be using this function otherwise. 

   Maths::Regression::Linear A(n, x, y);
   return A.getValue(a);
}

}

}

#endif
///////////////////////////////////////////
///////////////////////////////////////////
int main()
{
srand(time(NULL));
int Vect[2*N]={0},Force[N]={0};
//VARIABLES PARA HISTOGRAMA
int size=301;
double m[size];
/////////////////////////
inicializarfuerzas(Vect);
/*for(int i=0;i<2*N;i++)  PRINTF DE RECTIFICACION
		{
			printf(" Elemento [%d] = %d \n",i,Vect[i]);
		}	*/
for(int time=0;time<TIME;time++)
{
	vectorfuerza(Vect,Force);
	/*for(int i=0;i<N;i++)  PRINTF DE RECTIFICACION
		{
			printf(" Elemento [%d] = %d \n",i,Force[i]);
		}	*/

	int unit =rand()%N; //NUMERO ENTRE 0 Y N-1
	int elegida = Force[unit]; //LA UNIDAD ELEGIDA
	//printf("Unit FUERA IF = %d ... %d \n",elegida,unit); PRINTF DE RECTIFICACION
	int frag = rand()%P,count=0; //RODANDO PARA VER SI SE VA A DESFRAGMENTAR O NO
		if(frag==0) // DEBO CAMBIARLO A DIFERENTE
		{	
				Desfragmentar(Vect,elegida,count);
			 //PASAMOS POR REFERENCIA PARA REDISTRIBUIR
		}
		else //SI SE VA A UNIR
		{
			int unit2 =rand()%N;
			int elegida2 = Force[unit2];
			//printf("Unit = %d ... %d \n",elegida2,unit2);
			//SI NO QUEREMOS QUE SE UNA UNIDAD CON ELLA MISMA COLOCAMOS DO-WHILE
			Union(Vect,elegida,elegida2);
		}
	/*int sumaa =0;
	for(int ii=0;ii<=N;ii++)
		{
			sumaa=sumaa+Vect[2*ii-1];
		}
	if(sumaa>N)
	{
		printf("En el paso %d se salio \n",time);
		printf("la vcaga %d \n",frag);
		printf("y el responsable %d \n",Vect[2*elegida-1]);
		}
	
		for(int i=0;i<N;i++) //IMPRIME VALOR DE LA FUERZA Y EN QUE UNIDAD  --- PRINTF DE RECTIFICACION
		{
		//	printf(" Unidad [%d] \t Fuerza [%d] \n",Vect[2*i],Vect[2*i+1]);
		}*/
if(time%10000==0)
	{
		int Data[N+1]={0},contador2=0;
		int v=time/10000;
		double Y[N] = {0.0},X[N]={0.0};
		
		
		Sacardatos(Data,Vect);
		cout<<"TIME = "<<time<<endl;
		for(int i=1;i<=N;i++)
		{
			if(Data[i]!=0) //número de unidades con fuerza i
			{
			//printf("%d,%d \n",i,Data[i]);
			Y[contador2]=Data[i];
			X[contador2]=i;
			contador2=contador2+1;
			}
		}
		double S[contador2]={0},n_s[contador2]={0};
		//VA LA PARTE DE COGER EL VECTOR Y CREAR LOS DATOS QUE NECESITE EN ESCALA LOG
		for(int i=1;i<=contador2;i++)
			{
			S[i-1]=log10(X[i-1]);
			n_s[i-1]=log10(Y[i-1]); //fuerza 1 la mando a contador 0
			}
		int truncamiento=80; //ESTO ES PARA PARAR EL AJUSTE
		if(contador2>=0) //CAMBIAR ESTO
		{
			m[v]=pendiente(contador2,S,n_s);
			printf("La pendiente es %lf \n",m[v]);
			printf("el contador es %d \n\n\n",contador2);
		}
		else
		{
		m[v]=pendiente(truncamiento,S,n_s);
		printf("La pendiente es %lf \n",m[v]);
		}
	} //FIN DEL IF PARA IMPRIMIR VERIFICACION

} //FIN DEL FOR TIME
	
int Data[N+1]={0};
	Sacardatos(Data,Vect);
	cout<<"iteracion N = "<< TIME<<endl;
		for(int i=1;i<=N;i++)
		{
			if(Data[i]!=0)
			{
			printf("%d,%d \n",i,Data[i]);
			}
		}
		for(int i=1;i<=size;i++)
		{
		printf("%d,%lf \n",10000*i,m[i]);
		}
return 0;
}

///////////////////////////////////////////////////////
void inicializarfuerzas(int Vect[])
{
	for (int i=0;i<N;i++)
	{
		if(i%2==0)
				{
				Vect[2*i+1] = 2;
				}
		else
		{
			Vect[2*i+1] = 0;
			} //ACÁ PODEMOS COLOCAR LA SEMILLA QUE QUERAMOS
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
			else
			{return;}
			
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

double pendiente(int n, double S[],double n_s[])
{
	Maths::Regression::Linear A(n, S, n_s);
 
    /*cout << "    Slope = " << A.getSlope() << endl;*/
    cout << "Intercept = " << A.getIntercept() <<endl;
    cout << "Regression coefficient = " << A.getCoefficient() << endl;
	
	return A.getSlope();
}




