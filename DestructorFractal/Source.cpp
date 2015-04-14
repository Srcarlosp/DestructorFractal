
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "Preparacion.h"
#include "Constantes.h"

using namespace std;

int cont = 0;
const char fl[] = "Text.txt";

vector<puntos> fractal[DIM][DIM];
vector<flowPoint> flow;

int main()
{
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
	while(cont<TOTAL_CICLES)
	{
		//Generacion de punto y radio
		fractal = erasePoints(center, radius, fractal);
		//Guardar cada x ciclos el fractal
		if(cont%CICLES == 0)
		{
			FILE *p = fopen("fractalStep" + cont + ".txt", "w");
			for(int i = 0; i < DIM; i++)
			{
				for(int ii = 0; ii < DIM; ii++)
				{
					for(int iii = 0; iii < vec[i][ii].size; iii++)
					{
						fprintf(p, "%f\t%f\n", fractal[i][ii][iii].x, fractal[i][ii][iii].y);
					}
				}
			}
		}
		cont++;
		}
	}

	system("pause");
}
