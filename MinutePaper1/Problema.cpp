/*
Programa para realizar el seminario 5
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "Seminario05"
#define tasaFPS 120

#include <iostream>
#include <sstream>
#include <GL\freeglut.h>
#include <Utilidades.h>

using namespace std;

static float alfa = 0;

void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0.3f, 1.0f);
}

void muestraFPS()
{
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	static int fotogramas = 0;
	int ahora, tiempo_transcurrido;

	// Cada vez que pase por aqui incremento los fotogramas
	fotogramas++;

	// Calculo el tiempo transcurrido
	ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempo_transcurrido = ahora - antes;
	// Si ha transcurrido un segundo mostrar los fotogramas
	if (tiempo_transcurrido >= 1000) {
		// Modificar la barra de titulos
		stringstream titulo;
		titulo << "FPS = " << fotogramas;
		glutSetWindowTitle(titulo.str().c_str());
		// Reinicio la cuenta de fotogramas
		fotogramas = 0;
		antes = ahora;
	}
}

void display()
// Función de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 4, 0, 0, 0, 0, -1, 0, 0);

	ejes();

	glColor3f(0, 0, 1);
	//glRotatef(-90, 0, 1, 0);
	//glRotatef(-90, 0, 0, 1);
	glutSolidCylinder(0.5, 0.5, 10, 1);
	glutSolidCube(0.25);

	/*
		gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);

	ejes();

	glColor3f(0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-90, 0, 0, 1);
	glutSolidCylinder(0.5, 0.5, 10, 1);
	glutSolidCube(0.25);
	*/
	glFlush();
}

void onReshape(GLint w, GLint h)
// Funcion de atencion al redimensionado
{
	// Se usa toda el area de dibujo
	glViewport(0, 0, w, h);

	// Definimos la camara (matriz de proyección)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio = (float)w / h;
	//cout << "Aspect Ratio: " << ratio << endl;

	/*CAMARA ORTOGRAFICA
	Ajustamos la vista a la dimension mas pequeña del viewport para
	poder ver la totalidad de la ventana del mundi real (2x2)
	if(w<h)
	glOrtho(-1,1,-1/ratio,1/ratio,0,10);
	else
	glOrtho(-1*ratio,1*ratio,-1,1,0,10);

	CAMARA PERSPECTIVA
	La razon de aspecto se pasa directamente a la camara perspectiva
	Como damos fijo el angulo vertical,el tamaño del dibujo solo se
	modifica cuando variamos la altura del viewport.*/
	//glOrtho(-1, 1 , -1 , 1, -1, 1);
	gluPerspective(60, ratio, 1, 10);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 200);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(onReshape);
	glutMainLoop();
}