/*
Programa para realizar la practica 6
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "Interfaz de Conduccion"
#define tasaFPS 60
#define Ancho 20
#define Alto 10

#include <iostream>
#include <sstream>
#include <ctime>
#include <GL\freeglut.h>
#include <Utilidades.h>

using namespace std;

GLfloat v0[3] = { 0,0,5 }, v1[3] = { 20,0,5 }, v2[3] = { 20,0,-5 }, v3[3] = { 0,0,-5 };

GLfloat v0Ini[3] = { 0,0,-5 }, v1Ini[3] = { 0,0,-15 }, v2Ini[3] = { 20,0,-15 }, v3Ini[3] = { 20,0,-5 };

void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);

	

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
		titulo << "Practica 6 - FPS = " << fotogramas;
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

	gluLookAt(10, 10, -20, 10, 0, 10, 0, 0, 1);

	ejes();

	glColor3f(0.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.0f, 0.0f);
	quad(v0Ini, v1Ini, v2Ini, v3Ini);
	for (int i = 0; i <= 20; i++) {
		GLfloat v0Aux[3] = { 0, 0, 5 + i*Alto };
		GLfloat v1Aux[3] = { 20, 0, 5 + i*Alto };
		GLfloat v2Aux[3] = { 20, 0, -5 + i*Alto };
		GLfloat v3Aux[3] = { 0, 0, -5 + i*Alto };
		quad(v0Aux, v3Aux, v2Aux, v1Aux);
	}

	glFlush();
	//glutSwapBuffers();
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

	gluPerspective(45, ratio, 1, 90);
}

void update()
{
	// Variar la variable entre frames sin control de tiempo
	//alfa += 0.5;
	muestraFPS();
	// Animacion coherente con el tiempo transcurrido

	// Inicialmente la hora de arranque
	static int antes = glutGet(GLUT_ELAPSED_TIME);

	//Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// Tiempo transcurrido
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;
	antes = ahora;

	// Encolar un evento de redibujo
	glutPostRedisplay();
}

void onTimer(int tiempo)
{
	// Sierve para re arrancar el reloj de cuenta atras
	glutTimerFunc(tiempo, onTimer, tiempo);

	update();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); //GLUT_DOUBLE
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 200);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(onReshape);
	//glutIdleFunc(update);
	//glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);

	glutMainLoop();
}