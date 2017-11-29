/*
Programa para realizar la practica 6
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "Interfaz de Conduccion"
#define tasaFPS 60
#define Ancho 8
#define Alto 1
#define AMPLITUD 15
#define PERIODO 75

#include <iostream>
#include <sstream>
#include <ctime>
#include <GL\freeglut.h>
#include <Utilidades.h>

using namespace std;

float velocidad, angulo;
float xCam, xTurn;
float zCam, zTurn;

float derivadaDe(float u)
{
	return ((2 * PI*AMPLITUD) / PERIODO)*cos(u*((2 * PI) / PERIODO));
}

float funcionDe(float u)
{
	return AMPLITUD * sin(u * ((2 * PI) / PERIODO));
}

void updateTitulo()
{
	stringstream titulo;
	titulo << PROYECTO << ". Velocidad: " << velocidad << " m/s";
	glutSetWindowTitle(titulo.str().c_str());
}

float *vectorN(float u)
{
	float vec[2] = { 0,0 };
	float base = 1 / (sqrt(1 + pow(derivadaDe(u), 2)));
	vec[0] = base*-1 * derivadaDe(u);
	vec[1] = base;
	return vec;
}

void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	angulo = atan(funcionDe(Alto)/ Alto);
	xCam = 0; 
	xTurn = 0;
	zCam = 0; 
	zTurn = 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(xCam, 1, zCam, xTurn, 0, zTurn, 0, 1, 0);

	glColor3f(0.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT, GL_FILL);

	for (int i = xCam/Alto; i <= 75 + xCam; i++) {
		float u = i*Alto;
		float u2 = (i + 1)*Alto;
		float fDe1 = funcionDe(u);
		float fDe2 = funcionDe(u2);
		float * vecN = vectorN(u);

		//GLfloat v0[3] = { u + vecN[0] * Ancho / 2 - 0.0, 0 ,vecN[1] * Ancho / 2 + fDe1 - 0.0};
		//GLfloat v3[3] = { u - vecN[0] * Ancho / 2 - 0.0, 0 ,vecN[1] * (-1 * Ancho) / 2 + fDe1 - 0.0};
		//GLfloat v1[3] = { u2 + vecN[0] * Ancho / 2 + 0.0, 0 ,vecN[1] * Ancho / 2 + fDe2 + 0.0 };
		//GLfloat v2[3] = { u2 - vecN[0] * Ancho / 2 + 0.0, 0 ,vecN[1] * (-1 * Ancho) / 2 + fDe2 + 0.0};

		GLfloat v0[3] = { u, 0, Ancho / 2 + fDe1 };
		GLfloat v1[3] = { u2, 0, Ancho / 2 + fDe2 };
		GLfloat v2[3] = { u2, 0, (-1*Ancho) / 2 + fDe2 };
		GLfloat v3[3] = { u, 0, (-1*Ancho) / 2 + fDe1 };

		quad(v0, v1, v2, v3, 10, 5);

	}

	updateTitulo();

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
	// Se usa camara perspectiva
	gluPerspective(45, ratio, 0.1, 1000);
}

void update()
{
	// Inicialmente la hora de arranque
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	//Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	// Tiempo transcurrido
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;
	
	xCam += velocidad * cos(angulo) * tiempo_transcurrido;
	zCam += velocidad * sin(angulo) * tiempo_transcurrido;

	xTurn = 10000 * cos(angulo);
	zTurn = 10000 * sin(angulo);

	// Encolar un evento de redibujo
	antes = ahora;
	glutPostRedisplay();
}

void onEspecialKey(int specialKey, int x, int y)
{
	switch (specialKey)
	{
		case GLUT_KEY_LEFT:
			angulo -= 0.25 * PI / 180;
			break;
		case GLUT_KEY_RIGHT:
			angulo += 0.25 * PI / 180;
			break;
		case GLUT_KEY_UP:
			velocidad += 0.1;
			break;
		case GLUT_KEY_DOWN:
			velocidad -= 0.1;
			if (velocidad < 0) { velocidad = 0.0; }
			break;
		default:
			break;
	}

	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 200);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(onReshape);
	glutIdleFunc(update);
	glutSpecialFunc(onEspecialKey);
	//glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);
	glutMainLoop();
}