
#include "Preparacion.h"
#include "Constantes.h"
#include <vector>
#include <cstdio>

using namespace std;

int prepareFile(const char *file, vector<puntos> (*vec)[DIM]) //Abre el archivo fractal y lo pone en la esquina superior de la matriz fractal
{
	puntos p;
	FILE * ofile = fopen(file,"r");
	while (fscanf(ofile, "%f %f", &p.x, &p.y) != EOF)
		vec[0][0].push_back(p);
	return 1;
}

int segmentPropagation(vector<puntos> (*vec)[DIM], flowPoint flow) //Funcion de propagacion de segmentos
{
	register vector<puntos> originalV = vec[flow.x][flow.y];
	int originalS = vec[flow.x][flow.y].size();
	vec[flow.x][flow.y].clear();

	//Para ahorrar operaciones calculamos posiciones y datos comparaciones una sola vez al inicio
	register float cX = 1.0 / flow.deep;
	cX += cX * (flow.x / flow.dim);
	register float cY = 1.0 / flow.deep;
	cY += cY * (flow.y / flow.dim);
	register int C1[2] = { flow.x, flow.y };
	register int C2[2] = { flow.x, flow.y + flow.dim };
	register int C3[2] = { flow.x + flow.dim, flow.y + flow.dim };
	register int C4[2] = { flow.x + flow.dim, flow.y };

	//Flujo de ordenacion de los puntos
	for (int i = 0; i < originalS; i++)
	{
		if (originalV[i].x < cX)
		{
			if ((originalV[i].y) < cY)
			{
				vec[C1[0]][C1[1]].push_back(originalV[i]);
			}
			else
			{
				vec[C2[0]][C2[1]].push_back(originalV[i]);
			}
		}
		else
		{
			if ((originalV[i].y) < cY)
			{
				vec[C4[0]][C4[1]].push_back(originalV[i]);
			}
			else
			{
				vec[C3[0]][C3[1]].push_back(originalV[i]);
			}
		}
	}
	return 1;
}

vector<flowPoint> flowControlGenerator(int dimIni)
{
	int dim = dimIni;
	int e = 1;
	flowPoint fP;
	vector<flowPoint> vec;

	//Bucle que genera el fuljo completo
	while (dim > 1)
	{
		for (int i = 0; i < e; i++)
			for (int ii = 0; ii < e; ii++)
			{
				fP.dim = dim/2;
				fP.x = dim*i;
				fP.y = dim*ii;
				fP.deep = e*2;
				vec.push_back(fP);
			}
		dim /= 2;
		//progresion cuadratica
		e *= 2;
	}
	return vec;
}