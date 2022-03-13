# write all the tests for strassens and standard algorithms, output data to graph or csv or something

from memory_profiler import memory_usage
import time
import strassens as sam
import csv
import standard as bam
import strassens_cutoff as samk
import numpy as np
import random as r


def rand_matrix(n):
    M = np.ndarray((n, n))
    for i in range(n):
        for j in range(n):
            M[i][j] = r.randrange(0, 10)
    return M


def time_usage(f, n_samples):
    time_avg = []
    time_dev = []
    for n in n_samples:
        samples = []
        for i in range(10):
            A = rand_matrix(n)
            B = rand_matrix(n)
            print(n)
            start_time = time.process_time()
            f(A, B)
            end_time = time.process_time()
            samples.append(end_time - start_time)
        time_avg.append(sum(samples) / len(samples))
        time_dev.append(np.array(samples).std())
    return time_avg, time_dev


def write_to_csv(filepath, n, data_mean, data_dev):
    with open(filepath, 'w', newline='') as f:
        f.truncate()
        writer = csv.writer(f)
        for i in range(len(n)):
            writer.writerow([n[i], data_mean[i], data_dev[i]])


if __name__ == '__main__':
    r.seed()

    A = np.array([
        [3, 7],
        [6, 5]
    ])
    B = np.array([
        [3, 6],
        [5, 2]
    ])

    n_samples = []
    for i in range(13):
        n_samples.append(1 << i)

    C = sam.strassens(A, B)
    print(C)

    # sam_time_means, sam_time_devs = time_usage(lambda A, B : sam.strassens(A, B), n_samples)
    # write_to_csv('data/sam_time.csv', n_samples, sam_time_means, sam_time_devs)

    # bam_time_means, bam_time_devs = time_usage(lambda A, B : bam.multiply(A, B), n_samples)
    # write_to_csv('data/bam_time.csv', n_samples, bam_time_means, bam_time_devs)
