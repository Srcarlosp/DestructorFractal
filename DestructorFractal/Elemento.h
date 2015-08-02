#pragma once
#define TRACE_LONG 3000

class Elemento
{
public:
	//Parametros de dibujo
	enum RGB {rojo, verde, azul};
	float trace[TRACE_LONG][3];
	int tracePT = 0;
	unsigned char colorVec[3];
	float rad = 1.0F;
	//Parametros de la simulacion
	enum ejes { x, y, z };
	float posVec[3];
	float velVec[3];
	double accVec[3];
	double forVec[3];
	double mass = 1;
	//Metodos del objeto dibujo
	void setColor(unsigned char r = 255, unsigned char v = 255, unsigned char a = 255);
	void setColor(int elem, Elemento *e, unsigned char r = 255, unsigned char v = 255, unsigned char a = 255);
	//metodos del objeto simulacion
	void setRad(float r);
	void setMass(float m);
	void setPos(float xx, float yy, float zz);
	void setVel(float xx, float yy, float zz);
	void setAcc(float xx, float yy, float zz);
	void setFor(float xx, float yy, float zz);
	void setZero(int elem, Elemento *e);
	//Metodos calculo
	void doCalculus(int dim, int elem, Elemento *e);
	void doMove(int elem, Elemento *e);
	void doDraw(int elem, Elemento *e, float scale = 1);
};

