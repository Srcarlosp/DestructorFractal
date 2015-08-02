#include <vector>
#include <cstdio>

void erasePoints(struct puntos center, float radius, vector<puntos> (*vec)[DIM])
{	

	int maxx, maxy, minx, miny;
	vector<puntos> auxvec;
//Determinacion de los extremos de los círculos redondeando para sobredimensionarlo
	maxx = (int) ((center.x + radius) / (LENGTH)); //+ 1; //Se divide el punto más alejado, centro + radio, entre la longitud de la división, para obtener un número entero que indique el cuadrado al que pertenece
	maxy = (int) ((center.y + radius) / (LENGTH)); //+ 1; //Conforme a la nomenclatura de la cuadrícula no haría falta sumar uno para redondear por lo alto
	minx = (int) ((center.x - radius) / (LENGTH)); //No haría falta restar uno para redondear por lo bajo
	miny = (int) ((center.y - radius) / (LENGTH));
//Borrar los puntos por fuera del cuadrado, copiandolos en otro vector que luego reemplaza al del vector fractal
	for(int i = minx; i <= maxx; i++)
	{
		for(int ii = miny; ii <= maxy; ii++)
		{
			vsize = vec[i][ii].size;
			for(int iii = 0; iii < vsize; iii++)
			{
				if(sqrt( (vec[i][ii][iii].x - center.x) * (vec[i][ii][iii].x - center.x) + (vec[i][ii][iii].y - center.y) * (veci][ii][iii].y - center.y) > radius)
				{
					auxvec.push_back(vec[i][ii][iii]); //Se guardan todos los puntos de fuera del círculo
				}
			}
			vec[i][ii].swap(auxvec); //Intercambia los valores de un vector por los del otro
		}
	}

}

