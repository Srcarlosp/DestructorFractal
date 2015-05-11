#pragma once

//La dimencion debe ser simepre 2^n siendo n cualquier entero 
const int DIM = 8;
const float SCALE = 0.0001;
const int CICLES = 20;
const int TOTAL_CICLES = 1000;
const int NUM_CIRCLES = 1000;
const float MU = 0.125;
const float SIGMA = 0.2;

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

struct circle
{
    puntos center;
    float radius;
};