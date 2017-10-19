/*
Programa para realizar el ejercicio relacionado con el Seminario 2
Dibujar primitivas y cambiar atributos de OpenGL
Dependencias: +freeglut
Autor: Josep Dols
*/

#define PROYECTO "SGI::S2E03::Listas"

#include <iostream>
#include <GL\freeglut.h>
#include <Utilidades.h>

using namespace std;

static GLfloat coordenadas[10];
static const GLfloat colores[15] = { 1,1,1, 1,0,1, 0,1,1, 1,1,0, 0,0,1 };
static const GLuint pentagono[5] = { 0,1,2,3,4 };

void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	float radio = 1;

	//Crear las coordenadas
	for (int i = 0; i < 10; i+=2) {
		coordenadas[i] = radio*cos((i / 2.0) * 2 * PI / 5);
		coordenadas[i + 1] = radio*sin((i / 2.0) * 2 * PI / 5);
	}

	// Habilitar los arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Rellenar los arrays
	glVertexPointer(2, GL_FLOAT, 0, coordenadas);
	glColorPointer(3, GL_FLOAT, 0, colores);

	glClearColor(0, 0, 0.3, 1);
}
void display()
{
	//cout << "Se produce un evento 'display'\n";
	glClear(GL_COLOR_BUFFER_BIT);

	// Mandar a dibujar
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_INT, pentagono);

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
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}