#pragma once
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>
#include "Constantes.h"

using namespace std;

void erasePoints(vector<punto> flow, vector<puntos>(*vec)[DIM], puntos center, float radius);
vector<punto> eraseFlow(struct puntos center, float radius, vector<puntos>(*vec)[DIM]);