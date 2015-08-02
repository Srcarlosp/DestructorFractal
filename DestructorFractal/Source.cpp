#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include <ctime>
#include <cmath>

#include "Preparacion.h"
#include "Constantes.h"
#include "Generador.h"
#include "Tratamiento.h"
#include "glut.h"
#include "Ojos.h"

//////////////////////////////////////////////////////////
//				Inicializacion ventana					//

Ojos vista;
void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(BYTE key, int x, int y);

#include "Ventana.h"

//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//				Inicializacion flujo					//

using namespace std;

int cont = 0;
int cont1 = 0;
char char_cont[1000];
const char fl[] = "Text.txt";

vector<puntos> fractal[DIM][DIM];
vector<flowPoint> flow;

//////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
	//Abre la ventana y GL
	inicializaVentana(argc, argv);


	////////////////////////////////////////////////////////////
	////						FLUJO						////
	
	//////////////////////////////////////////////////////
	//					Inicializacion					//
	circle *list_circles;

	list_circles = randGenerator(MU, SIGMA);

	prepareFile(fl, fractal);
	for (int i = 0; i < fractal[0][0].size(); i++)
	{
		printf("Hola mundo %f %f\n", fractal[0][0][i].x, fractal[0][0][i].y);
	}
	flow = flowControlGenerator(DIM);
	for (int i = 0; i < flow.size(); i++)
	{
		printf("Hola mundo %d %d %d %d\n", flow[i].dim, flow[i].x, flow[i].y, flow[i].deep);
		segmentPropagation(fractal, flow[i]);
	}
	for (int i = 0; i < DIM; i++)
		for (int ii = 0; ii < DIM; ii++)
		{
			printf("\nVECTOR %d %d\n\n", i, ii);
			for (int iii = 0; iii < fractal[i][ii].size(); iii++)
				printf("POINT %f %f\n", fractal[i][ii][iii].x, fractal[i][ii][iii].y);
		}
	
	//////////////////////////////////////////////////////


	for(cont = 0; cont<TOTAL_CICLES; cont++) //Numero total de ciclos de borrado
	{
		erasePoints(list_circles[cont].center, list_circles[cont].radius, fractal);
		
		/*
		if(cont%CICLES == 0 && cont != 0) //Guardar los datos cada n ciclos de todo el proceso en un documento 
		{
			std::string name0 = "Fractal_Cicle_" + std::to_string(cont) + ".txt";
			FILE * p = fopen( name0.data(), "w");

			std::string name1 = "Circles_" + std::to_string(cont) + ".txt";
			FILE * q = fopen( name1.data(), "w");

			for(int i = 0; i < DIM; i++)
			{
				for(int ii = 0; ii < DIM; ii++)
				{
					for(int iii = 0; iii < fractal[i][ii].size(); iii++)
					{
						fprintf(p, "\t%f\t%f\n", fractal[i][ii][iii].x, fractal[i][ii][iii].y);
						for(cont1 = cont - CICLES + 1; cont1 <= cont; cont1++)
							fprintf(q, "\t%f\t%f\t%f\n", list_circles[cont1].center.x, list_circles[cont1].center.y, list_circles[cont1].radius);

					}
				}
			}
		}
		fclose(p);
		fclose(q);
		*/
	}
	

	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	//				Interfaz Grafica					//

	glutMainLoop();

	//////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////
//				Funciones de GLUT					//

void OnDraw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(vista.o_x, vista.o_y, vista.o_z, // posicion del ojo
		0.0, 0.0, 0.0, // hacia que punto mira (0,0,0) 
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)

	//aqui es donde hay que poner el código de dibujo

	glDisable(GL_LIGHTING);
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			for (int ii = 0; ii < fractal[i][j].size(); ii++)
			{
				glBegin(GL_POINTS);
				glVertex3f((fractal[i][j][ii].x * VS_SCALE) - 50, 0, (fractal[i][j][ii].y * VS_SCALE) - 50);
				glEnd();
			}
		}
	}
	glEnable(GL_LIGHTING);

	glutWireCube(100);

	glutSwapBuffers(); //Cambia los buffer de dibujo, no borrar esta linea ni poner nada despues
}

void OnTimer(int value) //poner aqui el codigo de animacion
{

	vista.orbita();

	glutTimerFunc(10, OnTimer, 0); //Temporizador de actulizacion
	glutPostRedisplay(); //Actualizacion de pantalla

}

void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	if (key == 'r') vista.dif -= 0.001;
	if (key == 'f') vista.dif += 0.001;
	if (key == 't') vista.d += 1;
	if (key == 'g') vista.d -= 1;
	if (key == 'w') vista.o_y += 1;
	if (key == 's') vista.o_y -= 1;
}

//////////////////////////////////////////////////////
