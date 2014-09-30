#include <iostream>
#include <cstdio>
#include "Matrix.h"

extern "C" {
#include <GL/glut.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
}

using namespace std;

void key_press_callback(unsigned char key, int x, int y) {
	cout << "key press" << key << " " << x << " " << y << endl;
}

void display(void) {
} 

void reshape(int width, int height) {
	cout << "reshape " << width << " " << height << endl;
	glutPostRedisplay();
}

Matrix mat;
inline void testmatrix() {
	mat = Matrix(2, 2);
	for (int i = 0;i < mat.size1();i++) {
		for (int j = 0;j < mat.size2();j++) {
			mat(i, j) = i + j;
		}
	}
	//cout << mat.size1 () << " " << mat.size2() << endl;
	//Matrix b = 2. * mat * mat;
	mat *= 3.*mat;
	for (int i = 0;i < mat.size1();i++) {
		for (int j = 0;j < mat.size2();j++) {
			cout << mat(i, j) << " ";
		}
		cout << endl;
	}
	cout << "I get here" << endl;
}

int main (int argc, char *argv[])
{
	testmatrix();
	return 0;

	gsl_matrix * m = gsl_matrix_alloc(1000, 1000);

	gsl_matrix * a = gsl_matrix_alloc(1000, 1000);
	gsl_matrix * b = gsl_matrix_alloc(1000, 1000);

	for (int i = 0;i < (int)a->size1;i++) {
		for (int j = 0;j < (int)a->size2;j++) {
			gsl_matrix_set(a, i, j, (rand() % 10000)/100.);
			gsl_matrix_set(b, i, j, (rand() % 10000)/100.);
		}
	}
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 
					1., a, b, 
					0., m);

	//gsl_matrix_fprintf(stdout, m, "%g");

	gsl_matrix_free (m);
	gsl_matrix_free (b);
	gsl_matrix_free (a);

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
