extern "C" {
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
}

class Matrix {
public:
	gsl_matrix *__matrix;

	void free_matrix();

	Matrix();
	Matrix(int n, int m);
	~Matrix();

	int size1() const ;
	int size2() const;

	void set_all(double x);
	void set_zero();

	void swap(Matrix &b);
	Matrix & operator=(const Matrix &b);

	Matrix operator+(const Matrix &b) const ;
	Matrix operator-(const Matrix &b) const ;
	Matrix operator*(const Matrix &b) const ;

	Matrix & operator+=(const Matrix &b);
	Matrix & operator-=(const Matrix &b);

	Matrix & operator*=(const Matrix &b);
	Matrix & operator*=(const double &b);

	double & operator()(int i, int j);
	double & operator()(int i, int j) const;
};

Matrix operator*(double l, const Matrix &a); 
Matrix operator*(const Matrix &a, double b); 
