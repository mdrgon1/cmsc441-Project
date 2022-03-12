import numpy as np
import strassens
import standard


# performs strassens multiplication algorithm, switches to standard at cutoff k
def strassens_cutoff(A, B, k):

    # ensure dimensions are a power of 2
    n, m = A.shape
    dim = int(np.ceil(np.log2(n)))
    dim = 1 << dim
    if dim != n:
        A = np.pad(A, ((0, dim - n), (0, dim - n)), 'constant', constant_values=0)
        B = np.pad(B, ((0, dim - n), (0, dim - n)), 'constant', constant_values=0)

    # base case, matrices are 1x1
    if len(A) == 1 or len(B) == 1:
        return 1

    # switch to standard multiplication:
    if len(A) <= k or len(B) <= k:
        return standard.multiply(A, B)

    a, b, c, d = strassens.split_matrix(A)
    e, f, g, h = strassens.split_matrix(B)

    p1 = strassens_cutoff(a, f - h, k)
    p2 = strassens_cutoff(a + b, h, k)
    p3 = strassens_cutoff(c + d, e, k)
    p4 = strassens_cutoff(d, g - e, k)
    p5 = strassens_cutoff(a + d, e + h, k)
    p6 = strassens_cutoff(b - d, g + h, k)
    p7 = strassens_cutoff(a - c, e + f, k)

    c11 = p5 + p4 - p2 + p6
    c12 = p1 + p2
    c21 = p3 + p4
    c22 = p1 + p5 - p3 - p7

    c = np.vstack((np.hstack((c11, c12)), np.hstack((c21, c22))))

    return c[:n, :m]
