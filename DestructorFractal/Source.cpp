
///Proguntar lo de la distribución normal para numeros negativos
///Pasar el archivo con un indicador del ciclo
///Carlos terminar unas cosas

#include <vector>
#include <cstdio>
#include <cstdlib>
#include "Preparacion.h"
#include "Constantes.h"
#include "Generador.h"
#include "Tratamiento.h"

#define STR(x) x 

using namespace std;

int cont = 0;
const char fl[] = "Text.txt";

vector<puntos> fractal[DIM][DIM];
vector<flowPoint> flow;

int main()
{


	//////Actualizado por Luis///////
	circle *list_circles;

	list_circles= randGenerator(MU, SIGMA);

	prepareFile(fl, fractal);
	for (int i = 0; i < fractal[0][0].size(); i++)
	{
		printf("Hola mundo %f %f\n", fractal[0][0][i].x, fractal[0][0][i].y);
	}
	flow = flowControlGenerator(DIM);
	for (int i = 0; i < flow.size(); i++)
	{
		printf("Hola mundo %d %d %d %d\n", flow[i].dim, flow[i].x, flow[i].y, flow[i].deep);
		segmentPropagation(fractal, flow[i]);
	}
	for (int i = 0; i < DIM; i++)
		for (int ii = 0; ii < DIM; ii++)
		{
			printf("\nVECTOR %d %d\n\n", i, ii);
			for (int iii = 0; iii < fractal[i][ii].size(); iii++)
				printf("POINT %f %f\n", fractal[i][ii][iii].x, fractal[i][ii][iii].y);
		}

	//////Actualizado por Luis///////
	for(cont = 0; cont<TOTAL_CICLES; cont++)
	{
		erasePoints(list_circles[cont].center, list_circles[cont].radius, fractal);

		//Guardar cada x ciclos el fractal
		if(cont%CICLES == 0)
		{
			FILE *p = fopen("fractalCicle.txt", "w");///////Mirar para cambiar de int a string
			for(int i = 0; i < DIM; i++)
			{
				for(int ii = 0; ii < DIM; ii++)
				{
					for(int iii = 0; iii < fractal[i][ii].size(); iii++)
					{
						fprintf(p, "%f\t%f\n", fractal[i][ii][iii].x, fractal[i][ii][iii].y);
					}
				}
			}
		}
		
	}

	system("pause");
}
