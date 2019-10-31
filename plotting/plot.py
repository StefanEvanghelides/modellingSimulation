import matplotlib.pyplot as plt
import matplotlib
from mpl_toolkits import mplot3d
import multiprocessing
import numpy as np
import time
import sys, os, shutil
import glob
import math

matplotlib.use('Agg')

# Global "data" and "results" paths
dataDirectory = "data/"
dataPath = os.path.abspath(dataDirectory)
resultsDirectory = "plotting_result"
resultsPath = os.path.abspath(resultsDirectory)

# Global universe size.
# This should be the same as the UNI_MAX in src/utils/constants.h
UNI_MAX = 1000000

# Color set for the galaxy classes
DEFAULT_COLORS = ['white', 'lime', 'yellow', 'pink', 'cyan', 'orange', 'blue' ,'red']

# Define the marker size
DEFAULT_MARKER_SIZE = 3

def saveFigure(fig, file):
    # First, retrieve only the name of th file
    filename = os.path.basename(file)

    # Ensure that file is sent to the correct Results directory
    resultsFile = os.path.join(resultsPath, filename)

    # Save the plot
    fig.savefig(resultsFile + '.png', figsize=(15, 15), dpi=200)


# Plots the coordinates of stars for one iteration
def plot_stars(galaxyClasses, coordinates, filename):
    fig = plt.figure()
    axes = fig.add_subplot(111, projection='3d')
    axes.set_xlim(-100, UNI_MAX * 1.1)
    axes.set_ylim(-100, UNI_MAX * 1.1)
    axes.set_zlim(-100, UNI_MAX * 1.1)

    # Hide grid lines
    axes.grid(False)

    # Hide axes ticks
    axes.set_xticks([])
    axes.set_yticks([])
    axes.set_zticks([])
    axes.set_axis_off()

    # Set the background black
    axes.set_facecolor('black')

    # Prepare the stars to be plotted
    x = []
    y = []
    z = []
    for coord in coordinates:
        x.append(coord[0])
        y.append(coord[1])
        z.append(coord[2])

    # Determine the classes colors
    colors = []
    for galClass in galaxyClasses:
        if (galClass >= len(DEFAULT_COLORS)):
            galClass = 0
        colors.append(DEFAULT_COLORS[galClass])

    # Define the marker size.
    # Should be inverse proportional to the number of stars.
    markerSize = DEFAULT_MARKER_SIZE / math.log10(len(coordinates))

    wframe = None
    if wframe:
        axes.collections.remove(wframe)
    wframe = axes.scatter(x, y, z, s=markerSize, c=colors)

    saveFigure(fig, filename)

    plt.close()


def plot_file(file):
    coordinates = []
    galaxyClasses = []
    try:
        with open(file, 'r') as f:
            for line in f:
                # skip comment lines.
                if (line[0] == "#"):
                    continue

                # Split line into coordinates.
                line_data = line.split(';')
                
                # Retrieve the galaxy class and add it directly into the array
                galaxyClasses.append(int(line_data[0]))
                
                # From the rest of the line, only keep the location.
                line_data = line_data[1:4]
                
                # Convert coordinates from type string to type float.
                line_data = [float(coord) for coord in line_data]
                
                # Add them to the main coordinates array.
                coordinates.append(line_data)

    except Exception as e:
        print("ERROR: " + str(e))

    # Now plot the coordinates.
    plot_stars(galaxyClasses, coordinates, file)

def plot_data(files, dataPath=dataPath):
    print("Reading files from: " + str(dataPath))
    tstart = time.time()

    with multiprocessing.Pool(multiprocessing.cpu_count() - 1 or 1) as p:
        p.map(plot_file, files)

    elapsed_time = time.time() - tstart
    print("Rendered " + str(len(files)) + " frames in " + str(elapsed_time) + " seconds.")

if __name__ == '__main__':
    # Remove the existing Results directory, create an empty one
    if os.path.exists(resultsPath):
        shutil.rmtree(resultsPath)
    if not os.path.exists(resultsPath):
        os.makedirs(resultsPath)

    if os.path.exists(dataPath):
        # Read all files from directory.
        files = glob.glob(dataPath + "/*.dat")
        files = sorted(files)
        
        if len(files) > 0:
            plot_data(files) # This uses the global dataPath
        else:
            print("\n      Data directory is empty! Nothing to plot!")
            print("HINT: Run the program again!")
    else:
        print("\n      Data directory does not exists! Nothing to plot!")
        print("HINT: Data directory is generated automatically after running the simulation!\n")
