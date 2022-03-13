#pragma once
void print_matrix(float** M, int n);

void add(float** A, float** B, float**& C, int n);

void sub(float** A, float** B, float**& C, int n);

bool compare(float** A, float** B, int n);

void randomize_matrix(float**& M, int n);

void init_matrix(float**& M, int n);

void bam(float** A, float** B, float**& C, int n);

void samk(float** A, float** B, float**& C, int n, int k);