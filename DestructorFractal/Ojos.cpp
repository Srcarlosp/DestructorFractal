#include <math.h>

#include "Ojos.h"

void Ojos::orbita()
{
	float T = atan2f(o_z, o_x);
	T += dif;
	o_x = d*cosf(T);
	o_z = d*sinf(T);
}