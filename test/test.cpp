#include <iostream>
#include <cstdio>

#include "Eigen/Dense"

extern "C" {
#include <GL/glut.h>
}

using namespace std;
using namespace Eigen;

void key_press_callback(unsigned char key, int x, int y) {
	cout << "key press" << key << " " << x << " " << y << endl;
}

void display(void) {
} 

void reshape(int width, int height) {
	cout << "reshape " << width << " " << height << endl;
	glutPostRedisplay();
}

inline void testeigen() {
	MatrixXd m(10, 10);
	for (int i = 0;i < 10;i++) {
		for (int j = 0;j < 10;j++) {
			m(i, j) = i + j;
		}
	}
	//m *= m;
	cout << m << endl;
}

int main (int argc, char *argv[])
{
	testeigen();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutKeyboardFunc(key_press_callback);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();   
	return 0;
}
