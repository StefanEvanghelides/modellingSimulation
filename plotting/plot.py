import matplotlib.pyplot as plt
import matplotlib
from mpl_toolkits import mplot3d
import multiprocessing
from functools import partial
import numpy as np
import time
import sys, os, shutil
import glob
import math
import argparse

matplotlib.use('Agg')

# Global "data" and "results" paths
dataDirectory = "data"
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


# Arguments
parser = argparse.ArgumentParser(prog="ModSim", allow_abbrev=True)
parser.add_argument("directory", nargs="?", default="*",
                    help="Specify the data directory(ies). If it's not specified, \
                            than data from all directories will be plotted.\
                            Note: Program will pattern match the argument")
args = parser.parse_args()


def saveFigure(fig, results_directory, file):
    # First, retrieve only the name of the file
    filename = os.path.basename(file)

    # Ensure that file is sent to the correct Results directory
    resultsFile = os.path.join(results_directory, filename)

    # Save the plot
    fig.savefig(resultsFile + '.png', figsize=(15, 15), dpi=200)


# Plots the coordinates of stars for one iteration
def plot_stars(galaxyClasses, coordinates, results_directory, filename):
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

    saveFigure(fig, results_directory, filename)

    plt.close()


def plot_file(results_directory, file):
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
    plot_stars(galaxyClasses, coordinates, results_directory, file)


def plot_data(files, data_directory=dataPath, results_directory=resultsPath):
    print("Reading files from: " + str(data_directory))
    tstart = time.time()

    with multiprocessing.Pool(multiprocessing.cpu_count() - 1 or 1) as p:
        partial_function = partial(plot_file, results_directory)
        p.map(partial_function, files)

    elapsed_time = time.time() - tstart
    print("Rendered " + str(len(files)) + " frames in " + str(elapsed_time) + " seconds.")


if __name__ == '__main__':
    if not os.path.exists(dataPath):
        print("\n      Data directory does not exists! Nothing to plot!")
        print("HINT: Data directory is generated automatically after running the simulation!\n")
        sys.exit(0)

    # Read the directory names. 
    # The first element was the main directory. Remove it.
    data_directories = [x[0] for x in os.walk(dataPath)]
    data_directories = data_directories[1:]

    # Check the directory passed as argument.
    if args.directory is not "*":
        data_directories = [x for x in data_directories if args.directory in x]

    # Read all files from directory.
    for data_dir in data_directories:
        # If the results path does not exit, then create it.
        if not os.path.exists(resultsPath):
            os.makedirs(resultsPath)
        
        # Keep only the base name, not the full path
        data_dir_base = os.path.basename(data_dir)
        # Create a new directory based on the current data directory.
        results_directory = os.path.join(resultsPath, data_dir_base)

        if os.path.exists(results_directory):
            shutil.rmtree(results_directory)
        if not os.path.exists(results_directory):
            os.makedirs(results_directory)
        files = glob.glob(data_dir + "/*.dat")
        files = sorted(files)

        if len(files) < 1:
            print("\n      Data directory is empty! Nothing to plot!")
            print("HINT: Run the program again!")

        plot_data(files, data_directory=data_dir, results_directory=results_directory)

        # Just 1 iteration for now
        sys.exit(0)


