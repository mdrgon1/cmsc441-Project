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
    max_memory = 0;
}

void time_usage_bam(int samples[], int s, float*& mean, float*& std_dev) {
    cout << "testing time usage for bam" << endl;

    for (int i = 0; i < s; i++) {
        int n = samples[i];
        cout << n << endl;

        float time[10];
        for (int j = 0; j < 10; j++) {
            float** A;
            float** B;
            float** C;
            randomize_matrix(A, n);
            randomize_matrix(B, n);
            init_matrix(C, n);

            clock_t t = clock();
            bam(A, B, C, n);
            time[j] = float(clock() - t) / CLOCKS_PER_SEC;
            //print_matrix(C, n);
            delete_matrix(A, n);
            delete_matrix(B, n);
            delete_matrix(C, n);
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
        std_dev[i] /= 9.0;
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
        cout << n << endl;

        float time[10];
        for (int j = 0; j < 10; j++) {
            float** A;
            float** B;
            float** C;
            randomize_matrix(A, n);
            randomize_matrix(B, n);
            init_matrix(C, n);

            clock_t t = clock();
            samk(A, B, C, n, k);
            time[j] = float(clock() - t) / CLOCKS_PER_SEC;
            //print_matrix(C, n);      
            delete_matrix(A, n);
            delete_matrix(B, n);
            delete_matrix(C, n);
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
        std_dev[i] /= 9.0;
        std_dev[i] = sqrt(std_dev[i]);
    }
}