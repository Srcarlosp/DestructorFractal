
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "Preparacion.h"
#include "Constantes.h"

using namespace std;

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
	system("pause");
}
