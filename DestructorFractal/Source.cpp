#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Preparacion.h"
#include "Constantes.h"
#include "Generador.h"
#include "Tratamiento.h"

using namespace std;

int cont = 0;
int cont1 = 0;
char char_cont[1000];
const char fl[] = "Text.txt";

vector<puntos> fractal[DIM][DIM];
vector<flowPoint> flow;

int main()
{

	circle *list_circles;

	list_circles = randGenerator(MU, SIGMA);

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

	for(cont = 0; cont<TOTAL_CICLES; cont++)
	{
		erasePoints(list_circles[cont].center, list_circles[cont].radius, fractal);

		if(cont%CICLES == 0 && cont != 0)
		{
			std::string name0 = "Fractal_Cicle_" + std::to_string(cont) + ".txt";
			FILE * p = fopen( name0.data(), "w");

			std::string name1 = "Circles_" + std::to_string(cont) + ".txt";
			FILE * q = fopen( name1.data(), "w");

			for(int i = 0; i < DIM; i++)
			{
				for(int ii = 0; ii < DIM; ii++)
				{
					for(int iii = 0; iii < fractal[i][ii].size(); iii++)
					{
						fprintf(p, "%f\t%f\n", fractal[i][ii][iii].x, fractal[i][ii][iii].y);
						for(cont1 = cont - CICLES + 1; cont1 <= cont; cont1++)
							fprintf(q, "%f\t%f\t%f\n", list_circles[cont1].center.x, list_circles[cont1].center.y, list_circles[cont1].radius);

					}
				}
			}
			fclose(p);
			fclose(q);
		}
		
	}

	system("pause");
}
