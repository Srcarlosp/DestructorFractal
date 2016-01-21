#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Preparacion.h"
#include "Constantes.h"

using namespace std;

void createNamesFile(const char *file)
{
    int i, j, k, num[LEN], dim[LEN];
    FILE *p;
    for(i=10; i<20; i++){
        num[i-10] = i;
        dim[i-10] = 82;
    }
    
    p = fopen(file , "w");
    
    for(j=0;j<NUM;j++)
        for(k=0; k<10; k++)
            fprintf(p, "fractal%d_%d.txt\n", num[k], dim[j]);
    
    fclose(p);
    
}

void createNamesList(const char *file, vector<char *> *names)
{
    int i;
    FILE *p;
    
    p = fopen(file , "r");
    
    for(i=0; i<NUM_FRACTALS; i++)
    {
		names->push_back(new char[LEN + 1]);
		char tempchar[LEN + 1];
        fscanf(p, "%s\n", tempchar);
		strcpy((*names)[(names->size())-1], tempchar);
		printf("%d\n", (names->size()) - 1);
    }	
    
    fclose(p);
    
}


int prepareFile(const char *file, vector<puntos> (*vec)[DIM]) //Abre el archivo fractal y lo pone en la esquina superior de la matriz fractal
{
	int i, j;
	puntos p;
	FILE * ofile = fopen(file,"r");

	for (i = 0; i < DIM; i++)
		for (j = 0; j < DIM;j++)
			vec[i][j].clear();

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

////////////////////////////////////////////////////////////////

string initDataFile(const char *cFractalName)//Inicializa el archivo que se va a utilizar para guardar los datos
{
	ofstream outFile;

	string sval; //Usamos sstream para convertir la media y varianza en strings
	ostringstream convert;

	string sFractalName = string(cFractalName, 0, 20);//Transformamos el char* en string, el tercer par�metro indica la longitud del char*

	convert << "_m" << MU * 1000 << "_v" << SIGMA * 1000;
	sval = convert.str();

	sFractalName.insert(sFractalName.size() - 4, sval);//Insertamos los valores en el string

	outFile.open(sFractalName); //El nombre del fichero generado tiene el formato fractal"numero"_"dimension"_m"media"_v"varianza".txt
	outFile.close();

	return sFractalName;
}