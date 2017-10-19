/*
Programa para realizar el ejercicio relacionado con el Seminario 2
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "SGI::S2E02::Pentagono"

#include <iostream>
#include <GL\freeglut.h>
#include <Utilidades.h>

using namespace std;

static GLuint pentagono;

void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	pentagono = glGenLists(1);	// Id de la lista
	float radio = 1;

	//Crear la lista
	glNewList(pentagono, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 5; i++) {
		glVertex3f(radio*cos(i * 2 * PI / 5), radio*sin(i*2*PI/5),0);
	}
	glEnd();
	glEndList();

	glClearColor(0, 0, 0.3, 1);
}
void display()
{
	cout << "Se produce un evento 'display'\n";

	glClear(GL_COLOR_BUFFER_BIT);
	//glutSolidTeapot(0.5);
	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(1, 0, 0);
	glCallList(pentagono);

	glPolygonMode(GL_FRONT, GL_LINE);
	glColor3f(1, 1, 1);
	glCallList(pentagono);

	glPolygonMode(GL_FRONT, GL_POINT);
	glColor3f(1, 1, 0);
	glPointSize(10);
	glCallList(pentagono);
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