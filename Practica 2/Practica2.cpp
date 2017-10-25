/*
Programa para realizar el ejercicio relacionado con el Seminario 2
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "Estrella de David"

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
	//cout << "Se produce un evento 'display'\n";
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0.3);
	// Mandar a dibujar
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