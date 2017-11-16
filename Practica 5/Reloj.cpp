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

static GLuint marcasHorarias;

static float alfa = 0;
static float alfaSegundos = 0;

void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	marcasHorarias = glGenLists(1);
	glNewList(marcasHorarias, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0*0.7, -1.0*0.7, 0.0);
	glVertex3f(0.866, 0.5, 0.0);
	glVertex3f(0.866*0.7, 0.5*0.7, 0.0);
	glVertex3f(-0.866, 0.5, 0.0);
	glVertex3f(-0.866*0.7, 0.5*0.7, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0*0.7, -1.0*0.7, 0.0);
	glEnd();
	glEndList();
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

	gluLookAt(0, 4, 0, 0, 0, 0, 0, 0, 1);

	ejes();

	//glPushMatrix();
	glColor3f(0, 1, 0);
	glScalef(0.25, 0.25, 0.25);
	glRotatef(180, 0, 0, 1);
	for (int i = 0; i < 12; i++) {
		//glTranslatef(1.0, 0.0, 0.0);
		
		glRotatef(360/12, 0.0, 1.0, 0.0);
		//glTranslatef(1.0, 0, 0);
		glutSolidCone(1, 4, 10, 1);
		//glCallList(marcasHorarias);
	}
	//glPopMatrix();

	/*
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(1.0f, 0, 0);
	glRotatef((alfa / 2), 0, 0, 1);
	glutWireTeapot(0.7);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(-1.0f, 0, 0);
	glRotatef((alfa / 2), 0, 1, 0);
	glutWireTeapot(0.7);
	glPopMatrix();
	*/
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
	static const float omega = 3;	// Vueltas por segundo

									// Inicialmente la hora de arranque
	static int antes = glutGet(GLUT_ELAPSED_TIME);

	//Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// Tiempo transcurrido
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;

	alfa += omega * 360 * tiempo_transcurrido;
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
	//glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);

	glutMainLoop();
}