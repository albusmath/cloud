#include <algorithm>
#include "Matrix.h"

void Matrix::free_matrix() {
	if (this->__matrix != NULL) {
		gsl_matrix_free(this->__matrix);
	}
	this->__matrix = NULL;
}

Matrix::Matrix() {
	this->__matrix = NULL;
}

Matrix::Matrix(int s1, int s2) {
	this->__matrix = gsl_matrix_alloc(s1, s2);
}

Matrix::~Matrix() {
	free_matrix();
}

int Matrix::size1() const { return __matrix->size1; }
int Matrix::size2() const { return __matrix->size2; }

void Matrix::set_all(double x) {
	gsl_matrix_set_all(this->__matrix, x);
}

void Matrix::set_zero() {
	gsl_matrix_set_zero(this->__matrix);
}

void Matrix::swap(Matrix &b) {
	std::swap(this->__matrix, b.__matrix);
}

Matrix & Matrix::operator=(const Matrix &b) {
	if (this == &b) return *this;
	if (__matrix == NULL) {
		__matrix = gsl_matrix_alloc(b.size1(), b.size2());
	}
	gsl_matrix_memcpy(__matrix, b.__matrix);
	return *this;
}

Matrix Matrix::operator+(const Matrix &b) const {
	Matrix res(__matrix->size1, __matrix->size2);
	gsl_matrix_memcpy(res.__matrix, __matrix);
	gsl_matrix_add(res.__matrix, b.__matrix);
	return res;
}

Matrix Matrix::operator-(const Matrix &b) const {
	Matrix res(__matrix->size1, __matrix->size2);
	gsl_matrix_memcpy(res.__matrix, __matrix);
	gsl_matrix_sub(res.__matrix, b.__matrix);
	return res;
}

Matrix Matrix::operator*(const Matrix &b) const {
	Matrix res(__matrix->size1, __matrix->size2);
	gsl_matrix_memcpy(res.__matrix, __matrix);
	gsl_blas_dgemm(	CblasNoTrans, CblasNoTrans, 
					1., __matrix, b.__matrix,
					0., res.__matrix);
	return res;
}

Matrix & Matrix::operator+=(const Matrix &b) {
	gsl_matrix_add(this->__matrix, b.__matrix);
	return *this;
}

Matrix & Matrix::operator-=(const Matrix &b) {
	gsl_matrix_sub(this->__matrix, b.__matrix);
	return *this;
}

Matrix & Matrix::operator*=(const Matrix &b) {
	Matrix res;
	res = *this;
	gsl_blas_dgemm(	CblasNoTrans, CblasNoTrans, 
					1., __matrix, b.__matrix,
					0., res.__matrix);
	*this = res;
	return *this;
}

Matrix & Matrix::operator*=(const double &b) {
	gsl_matrix_scale(this->__matrix, b);
	return *this;
}

Matrix operator*(double b, const Matrix &a) {
	Matrix res(a.size1(), a.size2());
	gsl_matrix_memcpy(res.__matrix, a.__matrix);
	res *= b;
	return res;
}

Matrix operator*(const Matrix &a, double b) {
	return b*a;
}

double & Matrix::operator()(int i, int j) const {
	return *gsl_matrix_ptr(__matrix, i, j);
}

double & Matrix::operator()(int i, int j) {
	return *gsl_matrix_ptr(__matrix, i, j);
}
