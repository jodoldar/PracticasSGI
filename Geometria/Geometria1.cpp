/*
Programa para realizar el ejercicio relacionado con el Seminario 2
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "SGI::S2E01::Tetera"

#include <iostream>
#include <GL\freeglut.h>
#include "Utilidades.h"

using namespace std;

void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;
}
void display()
{
	cout << "Se produce un evento 'display'\n";
	glClearColor(0, 0, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	//glutSolidTeapot(0.5);
	glutWireTeapot(0.5);
	glFlush();
}

void reshape(GLint w, GLint h)
{
	cout << "Se produce un evento 'reshape'\n";
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(50, 200);
	glutCreateWindow("Primer programa en OpenGL");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}