# implement strassen's matrix multiplication algorithm
import numpy as np


# return matrix m split into 4 quadrants
def split_matrix(m):
    endx, endy = m.shape
    midx = endx // 2
    midy = endy // 2
    return m[:midx, :midy], m[:midx, midy:], m[midx:, :midy], m[midx:, midy:]


def strassens(A, B):

    # base case, matrices are 1x1
    if len(A) == 1 or len(B) == 1:
        return 1

    a, b, c, d = split_matrix(A)
    e, f, g, h = split_matrix(B)

    p1 = strassens(a, f - h)
    p2 = strassens(a + b, h)
    p3 = strassens(c + d, e)
    p4 = strassens(d, g - e)
    p5 = strassens(a + d, e + h)
    p6 = strassens(b - d, g + h)
    p7 = strassens(a - c, e + f)

    c11 = p5 + p4 - p2 + p6
    c12 = p1 + p2
    c21 = p3 + p4
    c22 = p1 + p5 - p3 - p7

    c = np.vstack((np.hstack((c11, c12)), np.hstack((c21, c22))))

    return c
