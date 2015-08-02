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


int j = 0;
circle *list_circles;
void iterations();

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

vector<puntos> fractal[DIM][DIM];
vector<flowPoint> flow;

//////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
	//Abre la ventana y GL
	inicializaVentana(argc, argv);

	//////////////////////////////////////////////////////
	//					Inicializacion					//

	//Segmentacion
	prepareFile("Text.txt", fractal);
	flow = flowControlGenerator(DIM);
	for (int i = 0; i < flow.size(); i++)
	{
		segmentPropagation(fractal, flow[i]);
	}

	//Borrado
	list_circles = randGenerator(MU, SIGMA);
	for(cont = 0; cont<TOTAL_CICLES; cont++)
	{
		erasePoints(eraseFlow(list_circles[cont].center, list_circles[cont].radius, fractal), fractal, list_circles[cont].center, list_circles[cont].radius);

		printf("CIRCULO %f %f %f\n", list_circles[cont].center.x, list_circles[cont].center.y, list_circles[cont].radius);
	}

	//Entra en el bucle de dibujo
	glutMainLoop();

}

//////////////////////////////////////////////////////
//				Funciones de GLUT					//

//Dibujo
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
//Actualizacion de pantalla
void OnTimer(int value) //poner aqui el codigo de animacion
{

	vista.orbita();

	glutTimerFunc(10, OnTimer, 0); //Temporizador de actulizacion
	glutPostRedisplay(); //Actualizacion de pantalla

}
//Interfaz
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	if (key == 'n')
	{
		j++;
		iterations();
	}	
}

//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//				Funciones de Main					//

void iterations()
{
	erasePoints(eraseFlow(list_circles[j].center, list_circles[j].radius, fractal), fractal, list_circles[j].center, list_circles[j].radius);
}

//////////////////////////////////////////////////////