#include <stdio.h>
#include <math.h>

inline float norma(double *v, bool prenorma = true, int dim = 3)
{
	double modulo = 0;
	for (int i=0; i<dim; i++)
		modulo += v[i] * v[i];
	modulo = sqrt(modulo);
	//if ((prenorma == true))
	//	for (int i=0; i<dim; i++) 
	//		v[i] = v[i]/modulo;
	return modulo;
}