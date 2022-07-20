import numpy as np
from skimage import measure
import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus'] = False
def fun(x, y, z):
    return (x**2+(9/4)*y**2+z**2-1)**3-x**2*z**3-(9/80)*y**2*z**3
x, y, z = np.mgrid[-2:2:100j, -2:2:100j, -2:2:100j]
vol = fun(x, y, z)
iso_val=0.0
verts, faces, _, _ = measure.marching_cubes(vol, iso_val, spacing=(0.1, 0.1, 0.1))
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_trisurf(verts[:, 0], verts[:,1], faces, verts[:, 2],color = 'red')
ax.view_init(15, -120)
plt.title('蜜雪冰城甜蜜蜜',color='red')
plt.rcParams['figure.dpi'] = 1500
plt.show()
