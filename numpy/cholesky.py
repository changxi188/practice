import numpy as np
from scipy import linalg

a = np.array([[2, -1, 0, 0, 0],
			  [-1, 3, -1, 0, 0],
			  [0, -1, 3, -1, 0],
			  [0, 0, -1, 3, -1],
			  [0, 0, 0, -1, 2]])

L = linalg.cholesky(a, lower = True)

print(L)

print(np.allclose(np.dot(L, L.T), a))
