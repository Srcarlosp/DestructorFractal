#include <vector>
#include <cstdio>

vector<puntos> erasePoints(struct puntos center, float radius, vector<puntos> (*vec)[DIM])
{	

	int maxx, maxy, minx, miny;
	vector<puntos> auxvec;
//Determinacion de los extremos del círculos redondeando para sobredimensionarlo
	maxx = (int) ((center.x + radius) / (DIM * SCALE)) + 1;
	maxy = (int) ((center.y + radius) / (DIM * SCALE)) + 1;
	minx = (int) ((center.x - radius) / (DIM * SCALE));
	miny = (int) ((center.y - radius) / (DIM * SCALE));
//Borrar los puntos por fuera del cuadrado, copiandolos en otro vector que luego reemplaza al del vector fractal
	for(int i = minx; i <= maxx; i++)
	{
		for(int ii = miny; ii <= maxy; ii++)
		{
			vsize = vec[i][ii].size;
			for(int iii = 0; iii < vsize; iii++)
			{
				if(sqrt( (vec[i][ii][iii].x - center.x) * (vec[i][ii][iii].x - center.x) + (vec[i][ii][iii].y - center.y) * (veci][ii][iii].y - center.y) <= radius)
				{
					auxvec.push_back(vec[i][ii][iii]);
				}
			}
			vec[i][ii].swap(auxvec);
		}
	}

}

