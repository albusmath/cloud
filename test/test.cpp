#include <iostream>
#include <cstdio>

#include "Eigen/Dense"

extern "C" {
#include <GL/glut.h>
}

using namespace std;
using namespace Eigen;

const int maxn = 100;
const double FPS = 30.;

Vector3d position[maxn], velocity[maxn];

void key_press_callback(unsigned char key, int x, int y) {
	cout << "key press" << key << " " << x << " " << y << endl;
}

static void idle(void) {
	static double time = 0.;
	static int count = 0;
	double cur = glutGet(GLUT_ELAPSED_TIME);
	if ((cur - time) < 1000./FPS) {
		return ;
	}
	time = cur;
	count ++;
	cout << "FPS = " << 1000./(cur / count) << endl;
	glutPostRedisplay();
}

inline void run() {
	double dt = 1./FPS;
	for (int i = 0;i < maxn;i++) {
		position[i] += velocity[i] * dt;
	}
}

void display(void) {
	//cout << "display " << endl;
	run();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(0., 0., -5.);
	glScaled(.2, .2, .2);

	glBegin(GL_POINTS);
	for (int i = 0;i < maxn;i++) {
		glVertex3d(position[i](0), position[i](1), position[i](2));
	}
	//cout << position[0] << endl;
	glEnd();
	glutWireCube(5.);
	glutSwapBuffers();
}

void reshape(int x, int y) {
	cout << "reshape " << x << " " << y << endl;
	glutPostRedisplay();
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main (int argc, char *argv[])
{
	for (int i = 0;i < maxn;i++) {
		velocity[i] = Vector3d(rand()%100, rand()%100, rand()%100)/100. - Vector3d(50, 50, 50)/100.;
	}
	cout << velocity[0] << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutKeyboardFunc(key_press_callback);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();   
	return 0;
}
