# write all the tests for strassens and standard algorithms, output data to graph or csv or something

import strassens as sam
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


if __name__ == '__main__':
    r.seed()

    space_usage = []
    for i in range(1, 500, 10):
        A = rand_matrix(10)
        B = rand_matrix(10)
        sam.strassens(A, B)
