#include <iostream>
#include <time.h>
#include <cmath>
#include "matrix.h"
#include "testing.h"

using namespace std;

SIZE_T max_memory;

SIZE_T get_memory() {
    PROCESS_MEMORY_COUNTERS memCounter;
    BOOL result = K32GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
    return memCounter.WorkingSetSize;
}

void update_max_memory() {
    max_memory = max(max_memory, get_memory());
}

void reset_max_memory() {
    max_memory = get_memory();
}

void time_usage_bam(int samples[], int s, float*& mean, float*& std_dev) {
    cout << "testing time usage for bam" << endl;

    for (int i = 0; i < s; i++) {
        int n = samples[i];
        cout << "n = " << n << endl;

        float time[10];
        for (int j = 0; j < 10; j++) {
            MatrixWrapper A(nullptr, n);
            MatrixWrapper B(nullptr, n);
            MatrixWrapper C = init_matrix_wrapper(n);
            randomize_matrix_data(A._data, n);
            randomize_matrix_data(B._data, n);

            clock_t t = clock();
            bam(A, B, C);
            time[j] = float(clock() - t);
            //print_matrix(C, n);
            delete_matrix_data(A._data, n);
            delete_matrix_data(B._data, n);
            delete_matrix_data(C._data, n);
        }

        mean[i] = 0.0;
        for (int j = 0; j < 10; j++) {
            mean[i] += time[j];
        }
        mean[i] /= 10.0;

        std_dev[i] = 0.0;
        for (int j = 0; j < 10; j++) {
            std_dev[i] += (mean[i] - time[j]) * (mean[i] - time[j]);
        }
        std_dev[i] /= 10.0;
        std_dev[i] = sqrt(std_dev[i]);
    }
}

void time_usage_samk(int samples[], int s, int k, float*& mean, float*& std_dev) {
    if (k == 0)
        cout << "testing time usage for sam" << endl;
    else
        cout << "testing time usage for samk, k = " << k << endl;

    for (int i = 0; i < s; i++) {
        int n = samples[i];
        cout << "n = " << n << endl;

        float time[5];
        for (int j = 0; j < 5; j++) {
            MatrixWrapper A(nullptr, n);
            MatrixWrapper B(nullptr, n);
            MatrixWrapper C = init_matrix_wrapper(n);
            randomize_matrix_data(A._data, n);
            randomize_matrix_data(B._data, n);

            clock_t t = clock();
            samk(A, B, C, k);
            time[j] = float(clock() - t);
            //print_matrix(C, n);
            delete_matrix_data(A._data, n);
            delete_matrix_data(B._data, n);
            delete_matrix_data(C._data, n);
        }

        mean[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            mean[i] += time[j];
        }
        mean[i] /= 5.0;

        std_dev[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            std_dev[i] += (mean[i] - time[j]) * (mean[i] - time[j]);
        }
        std_dev[i] /= 5.0;
        std_dev[i] = sqrt(std_dev[i]);
    }
}

void speedup_foreach_k(int samples[], int s, int n, float*& mean, float*& std_dev) {
    cout << "testing percent speedup of samk for n = " << n << endl;

    clock_t sam_time = 16793.2;
    //for (int i = 0; i < 5; i++) {
    //    MatrixWrapper A(nullptr, n);
    //    MatrixWrapper B(nullptr, n);
    //    MatrixWrapper C = init_matrix_wrapper(n);
    //    randomize_matrix_data(A._data, n);
    //    randomize_matrix_data(B._data, n);

    //    clock_t t = clock();
    //    sam(A, B, C);
    //    sam_time += float(clock() - t);
    //    //print_matrix(C, n);
    //    delete_matrix_data(A._data, n);
    //    delete_matrix_data(B._data, n);
    //    delete_matrix_data(C._data, n);
    //}
    //sam_time /= 5.0;

    for (int i = 0; i < s; i++) {
        int k = samples[i];
        cout << "k = " << k << endl;

        float speedup[5];
        for (int j = 0; j < 5; j++) {
            MatrixWrapper A(nullptr, n);
            MatrixWrapper B(nullptr, n);
            MatrixWrapper C = init_matrix_wrapper(n);
            randomize_matrix_data(A._data, n);
            randomize_matrix_data(B._data, n);

            clock_t t1 = clock();
            samk(A, B, C, k);
            t1 = clock() - t1;

            speedup[j] = (1.0 - float(t1) / sam_time);

            //print_matrix(C, n);      
            delete_matrix_data(A._data, n);
            delete_matrix_data(B._data, n);
            delete_matrix_data(C._data, n);
        }

        mean[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            mean[i] += speedup[j];
        }
        mean[i] /= 5.0;

        std_dev[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            std_dev[i] += (mean[i] - speedup[j]) * (mean[i] - speedup[j]);
        }
        std_dev[i] /= 5.0;
        std_dev[i] = sqrt(std_dev[i]);
    }
}

void space_usage_bam(int samples[], int s, float*& mean, float*& std_dev) {
    cout << "testing space usage for bam" << endl;
    for (int i = 0; i < s; i++) {
        int n = samples[i];
        cout << "n = " << n << endl;

        float mem[5];
        for (int j = 0; j < 5; j++) {
            size_t start_memory = get_memory();
            reset_max_memory();
            MatrixWrapper A(nullptr, n);
            MatrixWrapper B(nullptr, n);
            MatrixWrapper C = init_matrix_wrapper(n);
            randomize_matrix_data(A._data, n);
            randomize_matrix_data(B._data, n);

            update_max_memory();
            bam(A, B, C);
            mem[j] = float(max_memory - start_memory);

            //print_matrix(C, n);
            delete_matrix_data(A._data, n);
            delete_matrix_data(B._data, n);
            delete_matrix_data(C._data, n);
        }

        mean[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            mean[i] += mem[j];
        }
        mean[i] /= 5.0;

        std_dev[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            std_dev[i] += (mean[i] - mem[j]) * (mean[i] - mem[j]);
        }
        std_dev[i] /= 5.0;
        std_dev[i] = sqrt(std_dev[i]);
    }
}

void space_usage_samk(int samples[], int s, int k, float*& mean, float*& std_dev) {
    if (k == 0)
        cout << "testing space usage for sam" << endl;
    else
        cout << "testing space usage for samk, k = " << k << endl;

    for (int i = 0; i < s; i++) {
        int n = samples[i];
        cout << "n = " << n << endl;

        float mem[5];
        for (int j = 0; j < 5; j++) {
            size_t start_memory = get_memory();
            reset_max_memory();
            MatrixWrapper A(nullptr, n);
            MatrixWrapper B(nullptr, n);
            MatrixWrapper C = init_matrix_wrapper(n);
            randomize_matrix_data(A._data, n);
            randomize_matrix_data(B._data, n);

            update_max_memory();
            samk(A, B, C, k);
            mem[j] = float(max_memory - start_memory);

            //print_matrix(C, n);
            delete_matrix_data(A._data, n);
            delete_matrix_data(B._data, n);
            delete_matrix_data(C._data, n);
        }

        mean[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            mean[i] += mem[j];
        }
        mean[i] /= 5.0;

        std_dev[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            std_dev[i] += (mean[i] - mem[j]) * (mean[i] - mem[j]);
        }
        std_dev[i] /= 5.0;
        std_dev[i] = sqrt(std_dev[i]);
    }
}