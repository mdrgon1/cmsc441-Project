# implement standard matrix multiplication algorithm
import numpy as np


# A and B are square matrices, returns C = A * B
def multiply(A, B):
    n, m = A.shape

    C = np.ndarray((n, m))

    for i in range(n):
        for j in range(n):
            C[i][j] = 0
            for k in range(n):
                a = A[i][k]
                b = B[k][j]
                C[i][j] += a * b

    return C
