/*
Programa para realizar el ejercicio de la practica 4
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "Estrella 3D"

#include <iostream>
#include <GL\freeglut.h>
#include <Utilidades.h>

using namespace std;

static GLuint estrella;


void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	estrella = glGenLists(1);
	glNewList(estrella, GL_COMPILE);
		float radioExterno = 1.0, radioInterno = 0.7;
		glBegin(GL_TRIANGLE_STRIP);
			// Primer triangulo
			glVertex3f(0.0, 1.0, 0.0);
			glVertex3f(radioInterno*0.0, radioInterno*1.0, 0.0);
			glVertex3f(-0.866, -0.5, 0.0);
			glVertex3f(radioInterno*(-0.866), radioInterno*(-0.5), 0.0);
			glVertex3f(0.866, -0.5, 0.0);
			glVertex3f(radioInterno*0.866, radioInterno*(-0.5), 0.0);
			glVertex3f(0.0, 1.0, 0.0);
			glVertex3f(radioInterno*0.0, radioInterno*1.0, 0.0);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			// Segundo triangulo
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

	glClearColor(1, 1, 1, 1);
}
void display()
// Función de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(1, 4, 4, 0, 0, 0, 0, 1, 0);
	
	glEnable(GL_DEPTH_TEST);

	glColor3f(0, 0, 1);
	glutWireSphere(1, 20, 20);
	int angle = 0;
	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glRotatef(-angle, 0, 1, 0);
		glColor3f((float) i/6, (float)i/6, (float)(6-i)/6);
		glCallList(estrella);
		angle += 30;
		glPopMatrix();
		//cout << "Estrella n " << i + 1 << "Color: " << (float)i / 6 << " " << (float)i/6 << " " << (float)(6-i)/6 << endl;
	}

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

	gluPerspective(20, ratio, 1, 10);
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