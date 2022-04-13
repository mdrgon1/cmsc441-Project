#pragma once

struct MatrixWrapper {
	MatrixWrapper(float** M, int xfrom, int xto, int yfrom, int yto);
	MatrixWrapper(float** M, int width, int height);
	MatrixWrapper(float** M, int width);
	MatrixWrapper(MatrixWrapper M, int xfrom, int xto, int yfrom, int yto);

	int _xfrom, _xto, _yfrom, _yto;
	int _width, _height;
	float** _data;
};

void delete_matrix_data(float** M, int n);

void print_matrix(MatrixWrapper M);

void add(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C);

MatrixWrapper add(MatrixWrapper A, MatrixWrapper B);

void sub(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C);

bool compare(MatrixWrapper A, MatrixWrapper B);

void randomize_matrix_data(float**& M, int n);

void init_matrix_data(float**& M, int n);

MatrixWrapper init_matrix_wrapper(int n);

void bam(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C);

void sam(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C);

void samk(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C, int k);