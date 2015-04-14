#pragma once

//La dimencion debe ser simepre 2^n siendo n cualquier entero 
const int DIM = 8;
const float SCALE = 0.0001;//Añadido por Luis, escala del fractal
const int CICLES = 20;//Añadido por Luis, numero de bombardeos entre ficheros
const int TOTAL_CICLES = 1000//Añadido por Luis, numero total de bombardeos 

struct puntos
{
	float x = 0;
	float y = 0;
};

struct flowPoint
{
	int dim = 0;
	int x = 0;
	int y = 0;
	int deep = 0;
};