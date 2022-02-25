# implement standard matrix multiplication algorithm
import numpy as np


# A and B are square matrices, returns C = A * B
def multiply(A, B):
    n, m = A.shape

    C = np.array([])
    np.reshape(C, (n, n))

    for i in range(n):
        for j in range(n):
            C[i][j] = 0
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]

    return C
