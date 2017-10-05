/*
	Programa para realizar el ejercicio relacionado con la practica 1
	Autor: Josep Dols
*/

#include <iostream>
#include <GL\freeglut.h>

using namespace std;

void display()
{
	cout << "Se produce un evento 'display'\n";
	glClearColor(0, 0, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT);
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
	cout << "Hola Mundo running" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}