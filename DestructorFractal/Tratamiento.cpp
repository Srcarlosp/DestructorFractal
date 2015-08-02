#include "Tratamiento.h"

using namespace std;

vector <punto> eraseFlow(struct puntos center, float radius, vector<puntos>(*vec)[DIM])
{
	printf("Hola mundo %f %f %f\n", center.x, center.y, radius);

	//Se calculan un cuadrado que inscriba a la circunferencia
	int maxx, maxy, minx, miny;
	int rmaxx, rmaxy, rminx, rminy;
	maxx = ceil((float)(center.x + radius) * DIM);
	maxy = ceil((float)(center.y + radius) * DIM); 
	minx = floor((float)(center.x - radius) * DIM); 
	miny = floor((float)(center.y - radius) * DIM);

	//printf("Hola mundo\n %d\n %d\n %d\n %d\n", maxx, maxy, minx, miny);

	rmaxx = maxx < DIM ? maxx : DIM-1;
	rmaxy = maxy < DIM ? maxy : DIM-1;
	rminx = minx > 0 ? minx : 0;
	rminy = miny > 0 ? miny : 0;

	//printf("Hola mundo\n %d\n %d\n %d\n %d\n", rmaxx, rmaxy, rminx, rminy);

	//Se calcula el cuadrado inscrito en la circunferencia a partir de los datos del lado y el radio
	int w = maxx - minx, h = maxy - miny;
	int seccion;

	if (w == h)
	{
		seccion = ceil((float) w/2 - (radius * DIM * 0.7)); //Se calcula la mitad del lado y se resta una aproximacion del radio medido sobre la diagonal proyectado sobre el lado
	}
	else
	{
		if (h < w)
			seccion = ceil((float) h/ 2 - (radius * DIM * 0.7));
		else
			seccion = ceil((float) w/ 2 - (radius * DIM * 0.7));
	}

	vector<punto> flow;
	/*
	for (int i = rminx; i < (rmaxx); i++)
		for (int j = rminy; j < rmaxy; j++)
		{
			punto p(i, j);
			flow.push_back(p);
		}
	*/

	for (int i = rminx; i < (rminx + seccion); i++)
		for (int j = rminy; j < rmaxy; j++)
		{
			punto p(i, j);
			flow.push_back(p);
		}
	for (int i = (rmaxx - seccion); i < rmaxx; i++)
		for (int j = rminy; j < rmaxy; j++)
		{
			punto p(i, j);
			flow.push_back(p);
		}

	for (int i = (rminx + seccion); i < (rmaxx - seccion); i++)
		for (int j = rminy; j < (rminy + seccion); j++)
		{
			punto p(i, j);
			flow.push_back(p);
		}
	for (int i = (rminx + seccion); i < (rmaxx - seccion); i++)
		for (int j = (rmaxy - seccion); j < rmaxy; j++)
		{
			punto p(i, j);
			flow.push_back(p);
		}

	//printf("seccion %d\n", seccion);

	for (int i = (rminx + seccion); i < (rmaxx - seccion); i++)
		for (int j = (rminy + seccion); j < (rmaxy - seccion); j++)
			vec[i][j].clear();

	return flow;

}

void erasePoints(vector<punto> flow, vector<puntos>(*vec)[DIM], puntos center, float radius)
{		
	int flowSize;
	flowSize = flow.size();
	for(int i = 0; i < flowSize; i++)
	{
		int vsize;
		vector<puntos> auxvec;
		vsize = vec[flow[i].x][flow[i].y].size();
		for(int iii = 0; iii < vsize; iii++)
		{
			if (sqrt((vec[flow[i].x][flow[i].y][iii].x - center.x) * (vec[flow[i].x][flow[i].y][iii].x - center.x) + (vec[flow[i].x][flow[i].y][iii].y - center.y) * (vec[flow[i].x][flow[i].y][iii].y - center.y)) > radius)
				auxvec.push_back(vec[flow[i].x][flow[i].y][iii]); //Se guardan todos los puntos de fuera del círculo
		}
		vec[flow[i].x][flow[i].y].swap(auxvec); //Intercambia los valores de un vector por los del otro
	}

}

