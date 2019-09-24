import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import numpy as np
import time
import sys, os

def read_data(path, iters, stepsize):
	# for every iteration, a list of stars with x,y,z
	# this variable will become very large
	print("Reading files...")
	coords = [[[],[],[]]]

	for i in range(int(iters/stepsize)):
		filename = os.path.join(path, "step_"+str(i*10)+".dat")
		## IO part, read all the coords
		try:
			with open(filename, 'r') as f:
				coords.append([[],[],[]])
				for line_terminated in f:
					line = line_terminated.rstrip('\n')
					line_coords = line.split()
					if (line_coords[0] == "#"): # skip comments
						continue

					for j in range(3):
						coords[i][j].append(float(line_coords[j]))
		except OSError as e:
			print(e)
			pass #ignore missing files, continue looking for next file

	return coords

def plot_stars(coords):
	fig = plt.figure()
	axes = fig.add_subplot(111, projection='3d')
	axes.set_xlim(-500, 500)
	axes.set_ylim(-500, 500)
	axes.set_zlim(-500, 500)

	wframe = None
	tstart = time.time()
	for i in range(len(coords)):
		x = coords[i][0]
		y = coords[i][1]
		z = coords[i][2]

		if wframe:
			axes.collections.remove(wframe)
		wframe = axes.scatter(x, y, z, s=1.0, c='green')
		plt.pause(0.05)

	print('Average FPS: %f' % (100 / (time.time() - tstart)))


def main():
	# Update these
	result = "mpi_64_1000_1000_10"
	iters = 1000

	path = os.path.join(os.path.abspath("./TMP/behalf-master/results"), result)

	coords = read_data(path, iters, 10)
	plot_stars(coords)

if __name__ == '__main__':
	main()
