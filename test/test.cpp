#include <iostream>
#include <cstdio>

extern "C" {
#include <GL/glut.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
}

using namespace std;

int
main (int argc, char *argv[])
{
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
//	glutKeyboardFunc(key_press_callback);   
	//glutDisplayFunc(display);   
	//glutReshapeFunc(reshape);   
	glutMainLoop();   
	return 0;
}
