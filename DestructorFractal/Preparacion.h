#pragma once
#include <vector>
#include "Constantes.h"

using namespace std;

int prepareFile(const char *file, vector<puntos>(*vec)[DIM]); //Abre el archivo fractal y lo pone en la esquina superior de la matriz fractal

/*
Coje la matriz de Fractal, el avance y una posicion.
Divide la matriz fractal en 4 en funcion de la posicion de los puntos que contiene, cortando el archivo con una cruz centrada.
Pone los resultados de en la matriza fractal dejando la esquina superior izquierda en la posicion original, y mueve las demas esquinas a sus posiciones respectivas usando el avance:
Si el avance es 25 y epieza en la posicion [0,0] el cuadrante superior izquiedo almcenara todo lo que quede en la parte superior izquierda de la grafica en la posicion [0,0],
el superior derecho hara lo propio pero en la posison [25,0] y asi sucesivamente, quedando ocupados los cuadrantes [0,0][25,0][0,25][25,25]
*/
int segmentPropagation(vector<puntos>(*vec)[DIM], flowPoint flow); //Funcion de propagaciion de segmentos

/*
Apartir de la dimension de la matriz final genera una cadena de verctores que describe todas las posisciones sobre las que tiene que actuar el algoritmo "segmentPropagation"
para completar la division del fractal y dejar los datos organizados en la matriz Fractal.
Funciona aumetando la profundidad paso a paso hasta que la dimension de la submatriz siguinte para a ser 1, para cada nivel de profuncidad genera los puntos a los que hay que haceder
en el siguente siguendo una progresion cubica, correspondiendo estos a una matris inscrita en la inicial.
*/
vector<flowPoint> flowControlGenerator(int dimIni); //Genera un vector con las posiciones y el orden a comprobar