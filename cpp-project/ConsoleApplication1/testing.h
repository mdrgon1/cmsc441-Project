#pragma once
void time_usage_bam(int samples[], int s, float*& mean, float*& std_dev);

void time_usage_samk(int samples[], int s, int k, float*& mean, float*& std_dev);

void time_usage_foreach_k(int samples[], int s);