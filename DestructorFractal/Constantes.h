#pragma once

//La dimencion debe ser simepre 2^n siendo n cualquier entero 
const int DIM = 8;

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