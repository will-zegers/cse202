import sys
import numpy as np
from scipy.linalg import lu


def main():
    n = int(sys.stdin.readline())

    A = np.array([])
    for _ in range(n):
        A = np.append(A, np.array([int(i) for i in sys.stdin.readline().split()]))
    A = np.reshape(A, (n, n+1))

    pl, u = lu(A, permute_l = True)

    print(u)

    for row in u:
        print("%.6f" % row[n],end=' ')
main()