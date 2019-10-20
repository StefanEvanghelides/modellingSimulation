import matplotlib.pyplot as plt
import matplotlib
from mpl_toolkits import mplot3d
import multiprocessing
import numpy as np
import time
import sys, os, shutil
import glob

matplotlib.use('Agg')

# Global "data" and "results" paths
dataDirectory = "data/"
dataPath = os.path.abspath(dataDirectory)
resultsDirectory = "plotting_results"
resultsPath = os.path.abspath(resultsDirectory)
if os.path.exists(resultsPath):
    shutil.rmtree(resultsPath)
if not os.path.exists(resultsPath):
    os.makedirs(resultsPath)


def saveFigure(fig, file):
    # First, retrieve only the name of th file
    filename = os.path.basename(file)

    # Ensure that file is sent to the correct Results directory
    resultFile = os.path.join(resultsPath, filename)

    # Save the plot
    fig.savefig(resultFile + '.png', figsize=(15, 15), dpi=200)


# Plots the coordinates of stars for one iteration
def plot_stars(coordinates, filename):
    fig = plt.figure()
    axes = fig.add_subplot(111, projection='3d')
    axes.set_xlim(200, 1000)
    axes.set_ylim(200, 1000)
    axes.set_zlim(200, 1000)

    # Hide grid lines
    axes.grid(False)

    # Hide axes ticks
    axes.set_xticks([])
    axes.set_yticks([])
    axes.set_zticks([])
    axes.set_axis_off()

    axes.set_facecolor('black')

    wframe = None

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

    saveFigure(fig, filename)

    plt.close()


def plot_file(file):
    coordinates = []
    try:
        with open(file, 'r') as f:
            for line in f:
                # skip comment lines.
                if (line[0] == "#"):
                    continue

                # Split line into coordinates.
                line_coordinates = line.split(';')
                
                # Only keep the location.
                line_coordinates = line_coordinates[0:3]
                
                # Convert coordinates from type string to type float.
                line_coordinates = [float(coord) for coord in line_coordinates]
                
                # Add them to the main coordinates array.
                coordinates.append(line_coordinates)

    except Exception as e:
        print("ERROR: " + str(e))

    # Now plot the coordinates.
    plot_stars(coordinates, file)

def plot_data(dataPath=dataPath):
    print("Reading files from: " + str(dataPath))
    tstart = time.time()

    # Read all files from directory.
    files = glob.glob(dataPath + "/*.dat")
    files = sorted(files)
    
    with multiprocessing.Pool(multiprocessing.cpu_count() - 1 or 1) as p:
        p.map(plot_file, files)

    elapsed_time = time.time() - tstart
    print("Rendered " + str(len(files)) + " frames in " + str(elapsed_time) + " seconds.")

if __name__ == '__main__':
    if os.path.exists(dataPath):
        plot_data() # This uses the global dataPath
    else:
        print("Directory does not exists! Nothing to plot!")
