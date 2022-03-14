#include <iostream>
#include <cstdlib>
#include "matrix.h"
#include "testing.h"
#include <time.h>

using namespace std;

const int N = 8;
const int OPTIMAL_K = 128;

void test_time_usage() {
    int bam_samples[] = { 2, 4, 8, 16, 32, 64, 128, 256 };
    int samk_samples[] = { 2, 4, 8, 16, 32, 64, 128, 256 };
    int sam_samples[] = { 2, 4, 8, 16, 32, 64, 128, 256 };
    //int k_samples[] = { 32, 64, 128, 256, 512 };
    int k_samples[] = { 256 };

    float* mean_samk = new float[N];
    float* std_dev_samk = new float[N];
    time_usage_samk(samk_samples, N, OPTIMAL_K, mean_samk, std_dev_samk);

    float* mean_sam = new float[N];
    float* std_dev_sam = new float[N];
    time_usage_samk(sam_samples, N, 0, mean_sam, std_dev_sam);

    float* mean_bam = new float[N];
    float* std_dev_bam = new float[N];
    time_usage_bam(bam_samples, N, mean_bam, std_dev_bam);

    float* mean_speedup = new float[1];
    float* std_dev_speedup = new float[1];
    speedup_foreach_k(k_samples, 1, 512, mean_speedup, std_dev_speedup);

    std::cout << "samk mean times" << endl;
    for (int i = 0; i < N; i++)
        std::cout << mean_samk[i] << ",";
    std::cout << endl;
    std::cout << "samk time std devs" << endl;
    for (int i = 0; i < N; i++)
        std::cout << std_dev_samk[i] << ",";
    std::cout << endl;

    std::cout << "sam mean times" << endl;
    for (int i = 0; i < N; i++)
        std::cout << mean_sam[i] << ",";
    std::cout << endl;
    std::cout << "sam time std devs" << endl;
    for (int i = 0; i < N; i++)
        std::cout << std_dev_sam[i] << ",";
    std::cout << endl;

    std::cout << "bam mean times" << endl;
    for (int i = 0; i < N; i++)
        std::cout << mean_bam[i] << ",";
    std::cout << endl;
    std::cout << "bam time std devs" << endl;
    for (int i = 0; i < N; i++)
        std::cout << std_dev_bam[i] << ",";
    std::cout << endl;

    std::cout << "samk speedups" << endl;
    for (int i = 0; i < 4; i++)
        std::cout << mean_speedup[i] << ",";
    std::cout << endl;
    std::cout << "samk speedups std dev" << endl;
    for (int i = 0; i < 4; i++)
        std::cout << std_dev_speedup[i] << ",";
    std::cout << endl;

    cout << "TIME MEASURED IN CLOCK TICKS, CLOCK_TICKS_PER_SEC = " << CLOCKS_PER_SEC << endl;

    delete[] mean_samk;
    delete[] std_dev_samk;
    delete[] mean_sam;
    delete[] std_dev_sam;
    delete[] mean_bam;
    delete[] std_dev_bam;

    delete[] mean_speedup;
    delete[] std_dev_speedup;
}

void test_space_usage() {
    int bam_samples[] = { 2, 4, 8, 16, 32, 64, 128, 256 };
    int samk_samples[] = { 2, 4, 8, 16, 32, 64, 128, 256 };
    int sam_samples[] = { 2, 4, 8, 16, 32, 64, 128, 256 };

    float* mean_samk = new float[N];
    float* std_dev_samk = new float[N];
    space_usage_samk(samk_samples, N, OPTIMAL_K, mean_samk, std_dev_samk);

    float* mean_sam = new float[N];
    float* std_dev_sam = new float[N];
    space_usage_samk(sam_samples, N, 0, mean_sam, std_dev_sam);

    float* mean_bam = new float[N];
    float* std_dev_bam = new float[N];
    space_usage_bam(bam_samples, N, mean_bam, std_dev_bam);

    std::cout << "samk mean space usage" << endl;
    for (int i = 0; i < N; i++)
        std::cout << mean_samk[i] << ",";
    std::cout << endl;
    std::cout << "samk space std devs" << endl;
    for (int i = 0; i < N; i++)
        std::cout << std_dev_samk[i] << ",";
    std::cout << endl;

    std::cout << "sam mean space usage" << endl;
    for (int i = 0; i < N; i++)
        std::cout << mean_sam[i] << ",";
    std::cout << endl;
    std::cout << "sam space std devs" << endl;
    for (int i = 0; i < N; i++)
        std::cout << std_dev_sam[i] << ",";
    std::cout << endl;

    std::cout << "bam mean space usage" << endl;
    for (int i = 0; i < N; i++)
        std::cout << mean_bam[i] << ",";
    std::cout << endl;
    std::cout << "bam space std devs" << endl;
    for (int i = 0; i < N; i++)
        std::cout << std_dev_bam[i] << ",";
    std::cout << endl;

    cout << "SPACE MEASURED IN BYTES" << endl;

    delete[] mean_samk;
    delete[] std_dev_samk;
    delete[] mean_sam;
    delete[] std_dev_sam;
    delete[] mean_bam;
    delete[] std_dev_bam;

    //delete[] mean_speedup;
    //delete[] std_dev_speedup;
}

int main() {

    int yuh;
    cout << "press enter to start" << endl;
    cin >> yuh;
    //std::cout << "memory: " << get_memory() << endl;

    test_space_usage();

    //_CrtDumpMemoryLeaks();

    return 0;
}
