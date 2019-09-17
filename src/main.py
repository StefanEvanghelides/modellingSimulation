'''
    This file is used to run the simulation and to plot the stars

    TODO: include the actual simulation.

    _Currently this just plots a few arbitrary 3D points_

'''

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

# Example input
xs = [1, 2, 3]
ys = [10, 15, 20]
zs = [5, 12, 18]

# Plotting
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(xs, ys, zs, marker='o')

ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
ax.set_zlabel('Z-axis')

plt.title('Colliding galaxies', y=1.15)
plt.show()
