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
#include "OpenGL.h"
#include "Ojos.h"
#include "boxCountingClean.h"


int j = 0;
int limit = 0, _percentage = 100, fractalNum = 0;
float percentage = 100 , dimension;
string dataFile;
circle *list_circles;
char cadena[10], namesFile[] = "Nombres.txt";
vector<char *> names;
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

	createNamesFile(namesFile);
	createNamesList(namesFile, &names);

	list_circles = randGenerator(MU, SIGMA);
	printf("%s\n", names[fractalNum]);
	prepareFile(names[fractalNum], fractal); //lista de nombres en el 5, para debug

	flow = flowControlGenerator(DIM);
	for (int i = 0; i < flow.size(); i++)
	{
		segmentPropagation(fractal, flow[i]);
	}

	/////////////////////////////////////////////////////////
	dataFile = initDataFile(names[fractalNum]);

	dimension = boxCounting(fullPointCounter(fractal), fractal);
	writeDataFile(dataFile, percentage, dimension, limit);
	fractalNum++;
	
	printf("Numero total de puntos: %d\n", fullPointCounter(fractal));
	printf("%f\n", dimension);
	//////////////////////////////////////////////////////


	//Entra en el bucle de dibujo
	glutMainLoop();

}

//////////////////////////////////////////////////////
//				Iteraciones							//

void iterations()
{

	erasePoints(eraseFlow(list_circles[j].center, list_circles[j].radius, fractal), fractal, list_circles[j].center, list_circles[j].radius);
	percentage = (float) 100 * fullPointCounter(fractal) / INITIAL_POINTS;
	printf("%f\n", percentage);
	limit++;
	if (_percentage - percentage >= 0.01)
	{
		_percentage = (int) percentage;
		dimension = boxCounting(fullPointCounter(fractal), fractal);
		writeDataFile(dataFile, percentage, dimension, limit);
	}
	if (_percentage < 75)
	{
		limit = 0;

		list_circles = randGenerator(MU, SIGMA);
		printf("%s\n", names[fractalNum]);
		prepareFile(names[fractalNum], fractal); //lista de nombres en el 5, para debug

		flow = flowControlGenerator(DIM);
		for (int i = 0; i < flow.size(); i++)
		{
			segmentPropagation(fractal, flow[i]);
		}

		_percentage = 100;
		percentage = 100;

		/////////////////////////////////////////////////////////
		dataFile = initDataFile(names[fractalNum]);

		dimension = boxCounting(fullPointCounter(fractal), fractal);
		writeDataFile(dataFile, percentage, dimension, limit);

		printf("Numero total de puntos: %d\n", fullPointCounter(fractal));
		printf("%f\n", dimension);

		fractalNum++;
	}
	
}

//////////////////////////////////////////////////////

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

	for (int i = 0; i < limit; i++)
	{
		glColor3ub(255, 2, 2);
		glTranslatef(((list_circles[i].center.x * VS_SCALE) - 50), 0, ((list_circles[i].center.y * VS_SCALE) - 50));
		glutWireSphere(list_circles[i].radius  * VS_SCALE, 16, 16);
		glTranslatef(-((list_circles[i].center.x * VS_SCALE) - 50), 0, -((list_circles[i].center.y * VS_SCALE) - 50));
		glutSolidSphere;
	}

	OpenGL::Print(cadena, 0, 0, 250, 250, 250);

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
	int i;
	if (key == 'n')
	{
		for (i = 0; i < 20; i++)
		{
			iterations();
			j++;
		}
	}
	/*
	if (key == 'b')
	{
		dimension = boxCounting(fullPointCounter(fractal), fractal);
		itoa(dimension * 10000, cadena, 10);
	}
	*/

}

//////////////////////////////////////////////////////