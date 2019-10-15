import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import numpy as np
import time
import sys, os
import glob


# Global figure variable
fig = plt.figure()


# Plots the coordinates of stars for one iteration
def plot_stars(coordinates):
    axes = fig.add_subplot(111, projection='3d')
    axes.set_xlim(-200, 1200)
    axes.set_ylim(-200, 1200)
    axes.set_zlim(-200, 1200)

    wframe = None
    tstart = time.time()
    x = []
    y = []
    z = []
    for coord in coordinates:
        x.append(coord[0])
        y.append(coord[1])
        z.append(coord[2])

    if wframe:
        axes.collections.remove(wframe)
    wframe = axes.scatter(x, y, z, s=1.0, c='green')
    plt.pause(0.05)

    elapsed_time = time.time() - tstart
    shown_time = "1000" # Current definition of infinity
    if (elapsed_time > 0.1):
        shown_time = str(100/elapsed_time)
    print("Average FPS: " + shown_time)


def plot_data(path):
    print("Reading files from: " + str(path))

    # Read all files from directory.
    files = glob.glob(path + "/*")

    # For each file, read its contents and plot it.
    for file in files:
        coordinates = []
        try:
            with open(file, 'r') as f:
                for line in f:
                    # skip comment lines.
                    if (line[0] == "#"):
                        continue

                    # Split line into coordinates.
                    line_coordinates = line.split()
                    
                    # Only keep the location.
                    line_coordinates = line_coordinates[0:3]
                    
                    # Convert coordinates from type string to type float.
                    line_coordinates = [float(coord) for coord in line_coordinates]
                    
                    # Add them to the main coordinates array.
                    coordinates.append(line_coordinates)

        except Exception as e:
            print("ERROR: " + str(e))

        # Now plot the coordinates.
        plot_stars(coordinates)

    # When the final iteration is reached,
    # figure should not disappear.
    plt.show()

if __name__ == '__main__':
    dataDirectory = "data"
    path = os.path.abspath(dataDirectory)
    plot_data(path)
