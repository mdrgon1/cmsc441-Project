#pragma once
#include <windows.h>
#include <Psapi.h>

SIZE_T get_memory();

void update_max_memory();

void reset_max_memory();

void time_usage_bam(int samples[], int s, float*& mean, float*& std_dev);

void time_usage_samk(int samples[], int s, int k, float*& mean, float*& std_dev);

void speedup_foreach_k(int samples[], int s, int n, float*& mean, float*& std_dev);

void space_usage_bam(int samples[], int s, float*& mean, float*& std_dev);

void space_usage_samk(int samples[], int s, int k, float*& mean, float*& std_dev);

