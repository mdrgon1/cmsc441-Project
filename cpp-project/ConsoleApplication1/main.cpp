#include <iostream>
#include <cstdlib>
#include "matrix.h"
#include "testing.h"

using namespace std;

const int N = 5;

int main() {

    int yuh;
    cout << "press enter to start" << endl;
    cin >> yuh;
    std::cout << "memory: " << get_memory() << endl;

    int bam_samples[] = { 2, 4, 8, 16, 32, 64, 128, 512 };
    int samk_samples[] = { 2, 4, 8, 16, 32, 64, 128, 512 };

    float* mean_samk = new float[N];
    float* std_dev_samk = new float[N];
    time_usage_samk(samk_samples, N, 32, mean_samk, std_dev_samk);

    float* mean_bam = new float[N];
    float* std_dev_bam = new float[N];
    time_usage_bam(bam_samples, N, mean_bam, std_dev_bam);

    std::cout << "sam_times" << endl;
    for (int i = 0; i < N; i++)
        std::cout << mean_samk[i] << ",";
    std::cout << endl;

    std::cout << "bam_times" << endl;
    for (int i = 0; i < N; i++)
        std::cout << mean_bam[i] << ",";
    std::cout << endl;

    std::cout << "memory: " << get_memory() << endl;

    delete[] mean_samk;
    delete[] std_dev_samk;

    delete[] mean_bam;
    delete[] std_dev_bam;

    std::cout << "memory: " << get_memory() << endl;
    //_CrtDumpMemoryLeaks();

    return 0;
}
