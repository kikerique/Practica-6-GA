#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void generaIndividuos(unsigned char*);
void seleccionaPadres(unsigned char*,float*);
void calculaDatos(unsigned char*,float*,float*);
void cruzaDeUnPunto(unsigned char*);
void cruzaDeDosPuntos(unsigned char*);
void cruzaUniforme(unsigned char*);
void cruzaAcentuada(unsigned char*);
void convierteBinario(unsigned char);
int main()
{
	unsigned char* individuos=(unsigned char*)malloc(sizeof(unsigned char)*6);
	int opc=0;
	generaIndividuos(individuos);
	printf("Selecciona una opcion de cruza\n1.-Cruza de un Punto\n2.-Cruza de Dos Puntos\n3.-Cruza Uniforme\n4.-Cruza Acentuada\n");
	scanf("%d",&opc);
	switch(opc)
	{
		case 1:
			cruzaDeUnPunto(individuos);
		break;
		case 2:
			cruzaDeDosPuntos(individuos);
		break;
		case 3:
			cruzaUniforme(individuos);
		break;
		case 4:
			cruzaAcentuada(individuos);
		break;
		default:
			printf("Selecciona una opcíon valida\n");
		break;
	}
	free(individuos);
	return 0;
}
void generaIndividuos(unsigned char* individuos)
{
	long ltime;
	ltime=time(NULL);
	int a,stime;
	stime=(unsigned)ltime/2;
	srand(stime);
	for(int i=0;i<6;i++)
	{
		individuos[i]=(unsigned char)(1+rand()%(255-1));
	}
}

void cruzaDeUnPunto(unsigned char* individuos)
{
	long ltime;
	ltime=time(NULL);
	int stime;
	stime=(unsigned)ltime/2;
	srand(stime);
	int puntoCruza=0;
	unsigned char bits,valor1,valor2,aux=0,hijo1,hijo2;
	for(int i=0;i<6;i=i+2)
	{
		aux=0;
		puntoCruza=rand()%(7);
		printf("Punto de Cruza: %d\n",puntoCruza);
		printf("Padre 1: ");
		convierteBinario(individuos[i]);
		printf("Padre 2: ");
		convierteBinario(individuos[i+1]);
		for(int j=7;j>7-puntoCruza;j--)
		{
			aux+=((unsigned char)(pow((double)2,(double)j)));
		}
		//aux=aux+1;
		//printf("Aux: %d\n",aux);
		
		valor1=aux&individuos[i];
		valor2=aux&individuos[i+1];
		/*printf("Bits del padre 1: %d\n",valor1);
		printf("Bits del padre 2: %d\n",valor2);*/
		hijo1=(individuos[i+1]-(valor2))+valor1;
		printf("Hijo 1: ");
		convierteBinario(hijo1);
		hijo2=(individuos[i]-(valor1))+valor2;
		printf("Hijo 2: ");
		convierteBinario(hijo2);
	}
}

void cruzaDeDosPuntos(unsigned char* individuos)
{
	long ltime;
	ltime=time(NULL);
	int stime;
	stime=(unsigned)ltime/2;
	srand(stime);
	int puntoCruza1=0,puntoCruza2=0;
	unsigned char valor1,valor2,aux=0,hijo1,hijo2;
	for(int i=0;i<6;i=i+2)
	{
		aux=0;
		puntoCruza1=1+rand()%(7);
		puntoCruza2=rand()%(puntoCruza1-1);
		printf("Puntos de Cruza: %d,%d\n",puntoCruza1,puntoCruza2);
		printf("Padre 1: ");
		convierteBinario(individuos[i]);
		printf("Padre 2: ");
		convierteBinario(individuos[i+1]);
		for(int j=7-puntoCruza2;j>7-puntoCruza1;j--)
		{
			aux+=((unsigned char)(pow((double)2,(double)j)));
		}
		//aux=aux+1;
		printf("Aux: %d\n",aux);
		
		valor1=aux&individuos[i];
		valor2=aux&individuos[i+1];
		/*printf("Bits del padre 1: %d\n",valor1);
		printf("Bits del padre 2: %d\n",valor2);*/
		hijo1=(individuos[i+1]-(valor2))+valor1;
		printf("Hijo 1: ");
		convierteBinario(hijo1);
		hijo2=(individuos[i]-(valor1))+valor2;
		printf("Hijo 2: ");
		convierteBinario(hijo2);
	}

}
void cruzaUniforme(unsigned char* individuos)
{
	long ltime;
	ltime=time(NULL);
	int stime;
	stime=(unsigned)ltime/2;
	srand(stime);
	unsigned char mascara=0;
	unsigned char valor1,valor2,aux=0,hijo1,hijo2;
	for(int i=0; i<6;i=i+2)
	{
		for(int j=7;j>=0;j--)
		{
			mascara+=(rand()%2)*pow(2,j);
		}
		printf("Mascara de copiado: ");
		convierteBinario(mascara);
		printf("Padre 1: ");
		convierteBinario(individuos[i]);
		printf("Padre 2: ");
		convierteBinario(individuos[i+1]);
		valor1=mascara&individuos[i];
		valor2=mascara&individuos[i+1];

		hijo1=(individuos[i+1]-valor2)+valor1;
		printf("Hijo 1: ");
		convierteBinario(hijo1);
		hijo2=(individuos[i]-(valor1))+valor2;
		printf("Hijo 2: ");
		convierteBinario(hijo2);
	}		
}
void cruzaAcentuada(unsigned char* individuos)
{
	long ltime;
	ltime=time(NULL);
	int stime;
	stime=(unsigned)ltime/2;
	srand(stime);
	unsigned char mascara=0;
	unsigned char aux=0,hijo1=0,hijo2=0,padre=0;
	for(int i=0; i<6;i=i+2)
	{
		for(int j=7;j>=0;j--)
		{
			mascara+=(rand()%2)*pow(2,j);
		}
		printf("Acentos: ");
		convierteBinario(mascara);
		printf("Padre 1: ");
		convierteBinario(individuos[i]);
		printf("Padre 2: ");
		convierteBinario(individuos[i+1]);
		for(int j=7;j>=0;j--)
		{
			if(mascara&(unsigned char)pow(2,j)){
				if(padre==0)
				{
					padre++;
				}else{
					padre=0;
				}
			}
			if(padre==0)
			{
				hijo1+=individuos[i]&(unsigned char)pow(2,j);
				hijo2+=individuos[i+1]&(unsigned char)pow(2,j);
			}else if(padre==1){
				hijo1+=individuos[i+1]&(unsigned char)pow(2,j);
				hijo2+=individuos[i]&(unsigned char)pow(2,j);
			}
		}
		printf("Hijo 1: ");
		convierteBinario(hijo1);
		printf("Hijo 2: ");
		convierteBinario(hijo2);
		hijo1=0;
		hijo2=0;
	}		

}
void convierteBinario(unsigned char numero)
{
	unsigned char n=128;
	while(n!=0)
	{
		if(n&numero)
		{
			printf("1");
		}else{
			printf("0");
		}
		n=n/2;
	}
	printf("\n");
}