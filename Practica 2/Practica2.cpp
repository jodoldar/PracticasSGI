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

static GLfloat coordenadas[12];
static GLuint estrella2[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
static GLuint estrella;
static const GLuint indices[36] = { 0,2,8, 2,10,8, 2,4,10, 4,6,10, 0,6,4, 0,8,6, 1,3,7, 7,3,9, 9,3,5, 9,5,11, 5,11,7, 5,7,1};

void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	

	estrella = glGenLists(1);
	glNewList(estrella, GL_COMPILE);

	float radioExterno = 1.0, radioInterno = 0.7;
	float desplazamiento = PI / 2;

	glBegin(GL_TRIANGLE_STRIP);
	//Crear las coordenadas
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.866, -0.5, 0.0);
	glVertex3f(0.7*0.0, 0.7*1.0, 0.0);
	glVertex3f(0.7*0.866, 0.7*(-0.5), 0.0);

	glVertex3f(0.866, -0.5, 0.0);
	glVertex3f(-0.866, -0.5, 0.0);
	glVertex3f(0.7*(-0.866), 0.7*(-0.5), 0.0);
	glVertex3f(0.7*0.866, 0.7*(-0.5), 0.0);

	glVertex3f(0.7*(-0.866), 0.7*(-0.5), 0.0);
	glVertex3f(-0.866, -0.5, 0.0);
	glVertex3f(0.7*0.0, 0.7*1.0, 0.0);
	glVertex3f(-0.866, -0.5, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	/**glVertex3f(radioInterno*cos(0 * (2 * PI) / 3 + desplazamiento), -sin(0 * (2 * PI) / 3 + desplazamiento),0.0);
	glVertex3f(radioExterno*cos(0 * (2 * PI) / 3 + desplazamiento), -sin(0 * (2 * PI) / 3 + desplazamiento), 0.0);

	glVertex3f(radioInterno*cos(1 * (2 * PI) / 3 + desplazamiento), -sin(1 * (2 * PI) / 3 + desplazamiento),0.0);
	glVertex3f(radioExterno*cos(1 * (2 * PI) / 3 + desplazamiento), -sin(1 * (2 * PI) / 3 + desplazamiento), 0.0);

	glVertex3f(radioInterno*cos(2 * (2 * PI) / 3 + desplazamiento), -sin(2 * (2 * PI) / 3 + desplazamiento),0.0);
	glVertex3f(radioExterno*cos(2*(2 * PI) / 3 + desplazamiento), -sin(2*(2 * PI) / 3 + desplazamiento),0.0);
	*/
	
	/*for (int i = 0; i < 6; i++) {
		glVertex3f(radioExterno*cos((i*PI/3 + desplazamiento) * 2 * PI / 6), radioExterno*sin((i*PI/3 + desplazamiento) * 2 * PI / 6), 0.0);
		//glVertex3f(radioInterno*cos((i*PI/6 + desplazamiento) * 2 * PI / 3), radioInterno*sin((i*PI/6 + desplazamiento) * 2 * PI / 3), 0.0);
	}*/
	glEnd();
	
	glEndList();
	glClearColor(1, 1, 1, 1);
}
void display()
{
	//cout << "Se produce un evento 'display'\n";
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
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