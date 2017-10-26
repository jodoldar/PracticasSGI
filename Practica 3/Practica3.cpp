/*
Programa para realizar el ejercicio de la practica 3
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "Mosaico"

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
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(0, 0, 0.8);
	
	//Estrella de arriba-izquierda
	glLoadIdentity();
	glTranslatef(-0.5, 0.5, 0.0);
	glRotatef(15, 0, 0, 1);
	glScalef(0.5, 0.5, 1);
	glCallList(estrella);

	glLoadIdentity();
	glTranslatef(-0.5, 0.5, 0.0);
	glRotatef(-15, 0, 0, 1);
	glScalef(0.5, 0.5, 1);
	glScalef(0.4, 0.4, 1);
	glCallList(estrella);

	//Estrella de arriba-derecha
	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0.0);
	glRotatef(-15, 0, 0, 1);
	glScalef(0.5, 0.5, 1);
	glCallList(estrella);

	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0.0);
	glRotatef(15, 0, 0, 1);
	glScalef(0.5, 0.5, 1);
	glScalef(0.4, 0.4, 1);
	glCallList(estrella);

	//Estrella de abajo-izquierda
	glLoadIdentity();
	glTranslatef(-0.5, -0.5, 0.0);
	glRotatef(-15, 0, 0, 1);
	glScalef(0.5, 0.5, 1);
	glCallList(estrella);

	glLoadIdentity();
	glTranslatef(-0.5, -0.5, 0.0);
	glRotatef(15, 0, 0, 1);
	glScalef(0.5, 0.5, 1);
	glScalef(0.4, 0.4, 1);
	glCallList(estrella);

	//Estrella de abajo-derecha
	glLoadIdentity();
	glTranslatef(0.5, -0.5, 0.0);
	glRotatef(15, 0, 0, 1);
	glScalef(0.5, 0.5, 1);
	glCallList(estrella);

	glLoadIdentity();
	glTranslatef(0.5, -0.5, 0.0);
	glRotatef(-15, 0, 0, 1);
	glScalef(0.5, 0.5, 1);
	glScalef(0.4, 0.4, 1);
	glCallList(estrella);

	glFlush();
}

void reshape(GLint w, GLint h)
{
	// cout << "Se produce un evento 'reshape'\n";
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 200);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}