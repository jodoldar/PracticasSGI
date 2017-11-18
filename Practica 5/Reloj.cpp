/*
Programa para realizar la practica 5
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "Reloj Analogico"
#define tasaFPS 60

#include <iostream>
#include <sstream>
#include <ctime>
#include <GL\freeglut.h>
#include <Utilidades.h>

using namespace std;

static GLuint aguja;

static float alfa = 0;
static float alfaSegundos = 0;
static float alfaMinutos = 0;
static float alfaHoras = 0;
static float anguloHoras = 360 / 12;
static float anguloMinutos = 360 / 60;

void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	time_t timeval;
	struct tm lclTime;

	time(&timeval);
	localtime_s(&lclTime, &timeval);

	printf("Current local time and date: %d:%d:%d %d/%d/%d\n", lclTime.tm_hour, lclTime.tm_min, lclTime.tm_sec, lclTime.tm_mday, lclTime.tm_mon+1, 1900+lclTime.tm_year);

	alfaSegundos = (lclTime.tm_sec / 60.0f) * 360;
	alfaMinutos = (lclTime.tm_min / 60.0f) * 360 + alfaSegundos/360;
	alfaHoras = ((lclTime.tm_hour%12) / 12.0f) * 360 + 30*(alfaMinutos/360);
	printf("Angulos: Horas: %f, Minutos: %f, Segundos: %f", alfaHoras, alfaMinutos, alfaSegundos);

	aguja = glGenLists(1);
	glNewList(aguja, GL_COMPILE);
		glBegin(GL_TRIANGLES);
			glVertex3f(0.0, 1.0, 0.0);
			glVertex3f(1.0, 0.0, 0.0);
			glVertex3f(-1.0, 0.0, 0.0);
		glEnd();
	glEndList();

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

	gluLookAt(-4, 4, 4, 0, 0, 0, 0, 0, 1);
	glScalef(0.9f, 0.9f, 0.9f);
	// Dibujo de las marcas horarias
	glColor3f(0, 1, 1);
	for (int i = 0; i < 12; i++) {
		glPushMatrix();
		glRotatef(anguloHoras*i, 0.0f, 1.0f, 0.0f);
		glScalef(1.0f, 1.0f, 2.0f);
		glTranslatef(0.0f, 0.0f, 1.0f);
		glutSolidCube(0.25);
		glPopMatrix();
	}

	// Dibujo de las marcas de los minutos
	glColor3f(0, 1, 0);
	for (int i = 0; i < 60; i++) {
		if (i % 5 != 0) {
			glPushMatrix();
			glRotatef(anguloMinutos*i, 0.0f, 1.0f, 0.0f);
			glScalef(0.25f, 1.0f, 1.0f);
			glTranslatef(0.0f, 0.0f, 2.0f);
			glutSolidCube(0.25);
			glPopMatrix();
		}
	}

	// Dibujo del segundero
	glColor3f(1, 0, 0);
	glPushMatrix();
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glRotatef(-alfaSegundos, 0.0f, 1.0f, 0.0f);
	glScalef(0.5f, 0.75f, 0.5f);
	glTranslatef(4.0f, 0.0f, 0.0f);
	glutSolidTorus(0.25, 0.6, 30, 30);
	glPopMatrix();

	// Dibujo del minutero
	glColor3f(1, 1, 0);
	glPushMatrix();
	glRotatef(-alfaMinutos, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 1.0f, 2.0f);
	glutSolidCone(0.25, 1, 10, 10);
	glPopMatrix();

	// Dibujo de las horas
	glColor3f(1.0, 0.0, 1.0);
	glPushMatrix();
	glRotatef(-alfaHoras, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.25f, 0.0f);
	glutSolidCone(0.25, 1, 10, 10);
	glPopMatrix();

	//glFlush();
	glutSwapBuffers();
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

	gluPerspective(60, ratio, 1, 10);
}

void update()
{
	// Variar la variable entre frames sin control de tiempo
	//alfa += 0.5;
	muestraFPS();
	// Animacion coherente con el tiempo transcurrido
	static const float omegaSegundos = 1/60.0f;	// Vueltas por segundo
	static const float omegaMinutos = 1 / 60.0f / 60.0f; // Vueltas por minuto
	static const float omegaHoras = 1 / 3600.0f / 12.0f; // Vueltas por hora
	// Inicialmente la hora de arranque
	static int antes = glutGet(GLUT_ELAPSED_TIME);

	//Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// Tiempo transcurrido
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;

	alfaSegundos += omegaSegundos * 360 * tiempo_transcurrido;
	alfaMinutos += omegaMinutos * 360 * tiempo_transcurrido;
	alfaHoras += omegaHoras * 360 * tiempo_transcurrido;

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 200);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(onReshape);
	//glutIdleFunc(update);
	glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);

	glutMainLoop();
}