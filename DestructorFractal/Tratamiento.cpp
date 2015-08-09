#include "Tratamiento.h"

using namespace std;

vector <punto> eraseFlow(struct puntos center, float radius, vector<puntos>(*vec)[DIM])
{
	//Se calculan un cuadrado que inscriba a la circunferencia
	int maxx, maxy, minx, miny;
	int rmaxx, rmaxy, rminx, rminy;
	maxx = ceil((float)(center.x + radius) * DIM);
	maxy = ceil((float)(center.y + radius) * DIM); 
	minx = floor((float)(center.x - radius) * DIM); 
	miny = floor((float)(center.y - radius) * DIM);

	rmaxx = maxx < DIM ? maxx : DIM-1;
	rmaxy = maxy < DIM ? maxy : DIM-1;
	rminx = minx > 0 ? minx : 0;
	rminy = miny > 0 ? miny : 0;

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

	for (int i = (rminx + seccion); i < (rmaxx - seccion); i++)
		for (int j = (rminy + seccion); j < (rmaxy - seccion); j++)
			vec[i][j].clear();

	return flow;

}

int fullPointCounter(vector<puntos>(*vec)[DIM])
{
	int retCount = 0;
	for (int i = 0; i < DIM; i++)
		for (int ii = 0; ii < DIM; ii++)
		{
			retCount += vec[i][ii].size();
		}
	return retCount;
}

void createStateList(float ** espacio, vector<puntos>(*vec)[DIM])
{
	int fullCount = 0;
	for (int i = 0; i < DIM; i++)
		for (int ii = 0; ii < DIM; ii++)
		{
			int vcount = vec[i][ii].size();
			for (int iii = 0; iii < vcount; iii++)
			{
				espacio[fullCount][0] = vec[i][ii][iii].x;
				espacio[fullCount][1] = vec[i][ii][iii].y;
				fullCount++;
			}
		}
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



