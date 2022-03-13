#include <iostream>
#include <cstdlib>
#include "matrix.h"
#include "testing.h"

using namespace std;

int main() {
    int bam_samples[] = { 10, 20, 30, 40 };
    int samk_samples[] = { 128 };

    float* mean_samk = new float[1];
    float* std_dev_samk = new float[1];
    time_usage_samk(samk_samples, 1, 0, mean_samk, std_dev_samk);

    float* mean_bam = new float[4];
    float* std_dev_bam = new float[4];
    time_usage_bam(bam_samples, 4, mean_bam, std_dev_bam);

    std::cout << "sam_times" << endl;
    for (int i = 0; i < 1; i++)
        std::cout << mean_samk[i] << ",";
    std::cout << endl;

    std::cout << "bam_times" << endl;
    for (int i = 0; i < 4; i++)
        std::cout << mean_bam[i] << ",";
    std::cout << endl;
}
