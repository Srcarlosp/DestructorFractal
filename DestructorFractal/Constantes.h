#pragma once

//La dimension debe ser simepre 2^n siendo n cualquier entero 
const int DIM = 256;	//Numero de divisiones de la cuadrícula

const int CICLES = 20;
const int TOTAL_CICLES = 1000;
const int NUM_CIRCLES = 1000; //Número de círculos para eliminar puntos
const float MU = 0.5;
const float SIGMA = 0.2;

//Constantes de ventana
#define WWW 800.0F
#define HHH 600.0F
#define PI 3.14159F
#define VS_SCALE 100

//tipos comunes
typedef unsigned char BYTE;

//
struct puntos
{
	float x = 0;
	float y = 0;
};

class punto
{
public :
	int x;
	int y;
	punto(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
};

struct flowPoint
{
	int dim = 0;
	int x = 0;
	int y = 0;
	int deep = 0;
};

struct circle
{
    puntos center;
    float radius;
};