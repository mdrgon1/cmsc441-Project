#include <iostream>
#include "matrix.h"
#include "testing.h"
#define MEASURE_SPACE

using namespace std;

void delete_matrix(float** M, int n) {
    for (int i = 0; i < n; i++) {
        delete[] M[i];
    }
    delete[] M;
}

void print_matrix(float** M, int n) {
    for (int i = 0; i < n; i++) {
        cout << "|";
        for (int j = 0; j < n; j++) {
            cout << M[j][i];
            cout << "|";
        }
        cout << endl;
    }
    cout << endl;
}

void add(float** A, float** B, float**& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void sub(float** A, float** B, float**& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

bool compare(float** A, float** B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != B[i][j])
                return false;
        }
    }
    return true;
}

void randomize_matrix(float**& M, int n) {
    M = new float* [n];
    for (int i = 0; i < n; i++) {
        M[i] = new float[n];
        for (int j = 0; j < n; j++) {
            M[i][j] = float(int(rand()) % 10);
        }
    }
}

void init_matrix(float**& M, int n) {
    M = new float* [n];
    for (int i = 0; i < n; i++) {
        M[i] = new float[n];
        for (int j = 0; j < n; j++) {
            M[i][j] = 0.0;
        }
    }
}

void bam(float** A, float** B, float**& C, int n) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[k][j] * B[i][k];
            }
        }
    }
#ifdef MEASURE_SPACE
    update_max_memory();
#endif
}


void samk(float** A, float** B, float**& C, int n, int k) {
    
    
    if (n == 1) {
#ifdef MEASURE_SPACE
        update_max_memory();
#endif
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    else if (n <= k) {
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

    delete_matrix(s[1], n / 2);
    delete_matrix(s[2], n / 2);
    delete_matrix(s[5], n / 2);
    delete_matrix(s[6], n / 2);

    float** p[7];
    for (int i = 0; i < 7; i++)
        init_matrix(p[i], n / 2);
    samk(s[0], m[0], p[0], n / 2, k);
    delete_matrix(s[0], n/2);
    delete_matrix(m[0], n / 2);

    samk(m[1], s[7], p[1], n / 2, k);
    delete_matrix(m[1], n / 2);
    delete_matrix(s[7], n / 2);

    samk(m[2], s[4], p[2], n / 2, k);
    delete_matrix(m[2], n / 2);
    delete_matrix(s[4], n / 2);

    samk(s[3], m[3], p[3], n / 2, k);
    delete_matrix(s[3], n / 2);
    delete_matrix(m[3], n / 2);

    samk(m[4], m[5], p[4], n / 2, k);
    delete_matrix(m[4], n / 2);
    delete_matrix(m[5], n / 2);

    samk(m[6], m[7], p[5], n / 2, k);
    delete_matrix(m[6], n / 2);
    delete_matrix(m[7], n / 2);

    samk(m[8], m[9], p[6], n / 2, k);
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
    for (int i = 0; i < 4; i++)
        delete_matrix(c[i], n / 2);
}