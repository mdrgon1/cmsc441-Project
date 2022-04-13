#include <iostream>
#include "matrix.h"
#include "testing.h"
//#define update_max_memory()

using namespace std;

void delete_matrix_data(float** M, int n) {
    for (int i = 0; i < n; i++) {
        delete[] M[i];
    }
    delete[] M;
}

void print_matrix(MatrixWrapper M) {
    for (int i = M._yfrom; i < M._yto; i++) {
        cout << "|";
        for (int j = M._xfrom; j < M._xto; j++) {
            cout << M._data[j][i];
            cout << "|";
        }
        cout << endl;
    }
    cout << endl;
}

void add(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C) {
    if (A._width != C._width || A._height != C._height || B._width != B._width || B._height != C._height)
        throw "matrices have mismatched dimensions!";
    int width = A._width;
    int height = A._height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            C._data[C._xfrom + i][C._yfrom + j] = A._data[A._xfrom + i][A._yfrom + j] + B._data[B._xfrom + i][B._yfrom + j];
        }
    }
}

void sub(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C) {
    if (A._width != C._width || A._height != C._height || B._width != B._width || B._height != C._height)
        throw "matrices have mismatched dimensions!";
    int width = A._width;
    int height = A._height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            C._data[C._xfrom + i][C._yfrom + j] = A._data[A._xfrom + i][A._yfrom + j] - B._data[B._xfrom + i][B._yfrom + j];
        }
    }
}

bool compare(MatrixWrapper A, MatrixWrapper B) {
    if (A._width != B._width || A._height != B._height)
        throw "matrices have mismatched dimensions!";
    for (int i = A._yfrom; i < A._yto; i++) {
        for (int j = A._xfrom; j < A._xto; j++) {
            if (A._data[i][j] != B._data[i][j])
                return false;
        }
    }
    return true;
}

void randomize_matrix_data(float**& M, int n) {
    M = new float* [n];
    for (int i = 0; i < n; i++) {
        M[i] = new float[n];
        for (int j = 0; j < n; j++) {
            M[i][j] = float(int(rand()) % 10);
        }
    }
}

void init_matrix_data(float**& M, int n) {
    M = new float* [n];
    for (int i = 0; i < n; i++) {
        M[i] = new float[n];
        for (int j = 0; j < n; j++) {
            M[i][j] = 0.0;
        }
    }
}

MatrixWrapper init_matrix_wrapper(int n) {
    float** data;
    init_matrix_data(data, n);
    MatrixWrapper M(data, n);
    return M;
}

void bam(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C) {
    update_max_memory();
    if (A._height != C._height || B._width != C._width || A._width != B._height)
        throw "matrices have mismatched dimensions!";
    for (int i = 0; i < B._width; i++)
    {
        for (int j = 0; j < A._width; j++)
        {
            C._data[C._xfrom + i][C._yfrom + j] = 0.0;
            for (int k = 0; k < A._width; k++)
            {
                C._data[C._xfrom + i][C._yfrom + j] += A._data[A._xfrom + k][A._yfrom + j] * B._data[B._xfrom + i][B._yfrom + k];
            }
        }
    }

    update_max_memory();
}

void sam(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C) {
    samk(A, B, C, 0);
}

void samk(MatrixWrapper A, MatrixWrapper B, MatrixWrapper C, int k) {
    if (A._width != C._width || A._height != C._height || B._width != B._width || B._height != C._height)
        throw "dimension mismatch!";
    if (C._width != C._height)
        throw "samk must be given square matrices";
    int n = A._width;
    update_max_memory();
    if (n == 1) {
        C._data[C._xfrom][C._yfrom] = A._data[A._xfrom][A._yfrom] * B._data[B._xfrom][B._yfrom];
        return;
    }
    else if (n <= k) {
        update_max_memory();
        bam(A, B, C);
        return;
    }
    int mid = n / 2;

    // split A and B into 4 matrices
    MatrixWrapper a(A, 0, mid, 0, mid);
    MatrixWrapper b(A, mid, n, 0, mid);
    MatrixWrapper c(A, 0, mid, mid, n);
    MatrixWrapper d(A, mid, n, mid, n);

    MatrixWrapper e(B, 0, mid, 0, mid);
    MatrixWrapper f(B, mid, n, 0, mid);
    MatrixWrapper g(B, 0, mid, mid, n);
    MatrixWrapper h(B, mid, n, mid, n);

    // hold intermediate sums
    MatrixWrapper s1 = init_matrix_wrapper(mid);
    MatrixWrapper s2 = init_matrix_wrapper(mid);
    MatrixWrapper s3 = init_matrix_wrapper(mid);
    MatrixWrapper s4 = init_matrix_wrapper(mid);
    MatrixWrapper s5 = init_matrix_wrapper(mid);
    MatrixWrapper s6 = init_matrix_wrapper(mid);
    MatrixWrapper s7 = init_matrix_wrapper(mid);
    MatrixWrapper s8 = init_matrix_wrapper(mid);
    MatrixWrapper s9 = init_matrix_wrapper(mid);
    MatrixWrapper s10 = init_matrix_wrapper(mid);

    // hold intermediate products
    MatrixWrapper p1 = init_matrix_wrapper(mid);
    MatrixWrapper p2 = init_matrix_wrapper(mid);
    MatrixWrapper p3 = init_matrix_wrapper(mid);
    MatrixWrapper p4 = init_matrix_wrapper(mid);
    MatrixWrapper p5 = init_matrix_wrapper(mid);
    MatrixWrapper p6 = init_matrix_wrapper(mid);
    MatrixWrapper p7 = init_matrix_wrapper(mid);
    update_max_memory();

    // calculate sums
    sub(f, h, s1);
    add(a, b, s2);
    add(c, d, s3);
    sub(g, e, s4);
    add(a, d, s5);
    add(e, h, s6);
    sub(b, d, s7);
    add(g, h, s8);
    sub(a, c, s9);
    add(e, f, s10);

    // calculate products;
    samk(a, s1, p1, k);
    delete_matrix_data(s1._data, mid);

    samk(s2, h, p2, k);
    delete_matrix_data(s2._data, mid);

    samk(s3, e, p3, k);
    delete_matrix_data(s3._data, mid);

    samk(d, s4, p4, k);
    delete_matrix_data(s4._data, mid);

    samk(s5, s6, p5, k);
    delete_matrix_data(s5._data, mid);
    delete_matrix_data(s6._data, mid);

    samk(s7, s8, p6, k);
    delete_matrix_data(s7._data, mid);
    delete_matrix_data(s8._data, mid);

    samk(s9, s10, p7, k);
    delete_matrix_data(s9._data, mid);
    delete_matrix_data(s10._data, mid);
    
    //print_matrix(p1);
    //print_matrix(p2);
    //print_matrix(p3);
    //print_matrix(p4);
    //print_matrix(p5);
    //print_matrix(p6);
    //print_matrix(p7);

    // split C into 4 matrices
    MatrixWrapper c1(C, 0, mid, 0, mid);
    MatrixWrapper c2(C, mid, n, 0, mid);
    MatrixWrapper c3(C, 0, mid, mid, n);
    MatrixWrapper c4(C, mid, n, mid, n);

    // calculate C
    add(p4, p5, c1);
    sub(c1, p2, c1);
    add(c1, p6, c1);

    add(p1, p2, c2);

    add(p3, p4, c3);

    add(p1, p5, c4);
    sub(c4, p3, c4);
    sub(c4, p7, c4);

    // clean up p matrices
    delete_matrix_data(p1._data, mid);
    delete_matrix_data(p2._data, mid);
    delete_matrix_data(p3._data, mid);
    delete_matrix_data(p4._data, mid);
    delete_matrix_data(p5._data, mid);
    delete_matrix_data(p6._data, mid);
    delete_matrix_data(p7._data, mid);
    update_max_memory();
}
/*
void samk(float** A, float** B, float**& C, int n, int k) {
    
    update_max_memory();
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    else if (n <= k) {
        update_max_memory();
        bam(A, B, C, n);
        return;
    }

    float** s[8];
    for (int i = 0; i < 8; i++)
        init_matrix(s[i], n / 2);
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            s[0][i][j] = A[i][j];
            s[1][i][j] = A[i + n / 2][j];
            s[2][i][j] = A[i][j + n / 2];
            s[3][i][j] = A[i + n / 2][j + n / 2];
            s[4][i][j] = B[i][j];
            s[5][i][j] = B[i + n / 2][j];
            s[6][i][j] = B[i][j + n / 2];
            s[7][i][j] = B[i + n / 2][j + n / 2];
        }
    }

    float** m[10];
    for (int i = 0; i < 10; i++)
        init_matrix(m[i], n / 2);
    sub(s[5], s[7], m[0], n / 2);
    add(s[0], s[1], m[1], n / 2);
    add(s[2], s[3], m[2], n / 2);
    sub(s[6], s[4], m[3], n / 2);
    add(s[0], s[3], m[4], n / 2);
    add(s[4], s[7], m[5], n / 2);
    sub(s[1], s[3], m[6], n / 2);
    add(s[6], s[7], m[7], n / 2);
    sub(s[0], s[2], m[8], n / 2);
    add(s[4], s[5], m[9], n / 2);

    update_max_memory();

    delete_matrix(s[1], n / 2);
    delete_matrix(s[2], n / 2);
    delete_matrix(s[5], n / 2);
    delete_matrix(s[6], n / 2);

    float** p[7];
    for (int i = 0; i < 7; i++)
        init_matrix(p[i], n / 2);
    samk(s[0], m[0], p[0], n / 2, k);
    update_max_memory();
    delete_matrix(s[0], n/2);
    delete_matrix(m[0], n / 2);

    samk(m[1], s[7], p[1], n / 2, k);
    update_max_memory();
    delete_matrix(m[1], n / 2);
    delete_matrix(s[7], n / 2);

    samk(m[2], s[4], p[2], n / 2, k);
    update_max_memory();
    delete_matrix(m[2], n / 2);
    delete_matrix(s[4], n / 2);

    samk(s[3], m[3], p[3], n / 2, k);
    update_max_memory();
    delete_matrix(s[3], n / 2);
    delete_matrix(m[3], n / 2);

    samk(m[4], m[5], p[4], n / 2, k);
    update_max_memory();
    delete_matrix(m[4], n / 2);
    delete_matrix(m[5], n / 2);

    samk(m[6], m[7], p[5], n / 2, k);
    update_max_memory();
    delete_matrix(m[6], n / 2);
    delete_matrix(m[7], n / 2);

    samk(m[8], m[9], p[6], n / 2, k);
    update_max_memory();
    delete_matrix(m[8], n / 2);
    delete_matrix(m[9], n / 2);

    float** c[4];
    for (int i = 0; i < 4; i++)
        init_matrix(c[i], n / 2);
    add(p[4], p[3], c[0], n / 2);
    add(c[0], p[5], c[0], n / 2);
    sub(c[0], p[1], c[0], n / 2);

    add(p[0], p[1], c[1], n / 2);

    add(p[2], p[3], c[2], n / 2);

    add(p[0], p[4], c[3], n / 2);
    sub(c[3], p[2], c[3], n / 2);
    sub(c[3], p[6], c[3], n / 2);
    update_max_memory();
    for (int i = 0; i < 7; i++)
        delete_matrix(p[i], n / 2);

    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            C[i][j] = c[0][i][j];
            C[i + n / 2][j] = c[1][i][j];
            C[i][j + n / 2] = c[2][i][j];
            C[i + n / 2][j + n / 2] = c[3][i][j];
        }
    }
    update_max_memory();
    for (int i = 0; i < 4; i++)
        delete_matrix(c[i], n / 2);
}*/

MatrixWrapper::MatrixWrapper(float** M, int xfrom, int xto, int yfrom, int yto) {
    _data = M;
    _xfrom = xfrom;
    _yfrom = yfrom;
    _xto = xto;
    _yto = yto;
    _width = xto - xfrom;
    _height = yto - yfrom;
}

MatrixWrapper::MatrixWrapper(float** M, int width, int height) {
    _data = M;
    _xfrom = 0;
    _yfrom = 0;
    _xto = width;
    _yto = height;
    _width = width;
    _height = height;
}

MatrixWrapper::MatrixWrapper(float** M, int width) {
    _data = M;
    _xfrom = 0;
    _yfrom = 0;
    _xto = width;
    _yto = width;
    _width = width;
    _height = width;
}

MatrixWrapper::MatrixWrapper(MatrixWrapper M, int xfrom, int xto, int yfrom, int yto) {
    _data = M._data;
    _xfrom = M._xfrom + xfrom;
    _xto = M._xfrom + xto;
    _yfrom = M._yfrom + yfrom;
    _yto = M._yfrom + yto;
    _width = xto - xfrom;
    _height = yto - yfrom;
}