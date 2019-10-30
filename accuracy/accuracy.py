import argparse
import numpy as np
import sys
import glob

def distance(coord1, coord2):
    dx = (coord1[0] - coord2[0])
    dy = (coord1[1] - coord2[1])
    dz = (coord1[2] - coord2[2])

    return np.sqrt(dx ** 2 + dy ** 2 + dz ** 2)

def avg_distance(coords1, coords2):
    distances = []
    for i in range(len(coords1)):
        d = distance(coords1[i], coords2[i])
        distances.append(d)
    return np.average(distances)

def get_coordinates(file):
    coordinates = []
    try:
        with open(file, 'r') as f:
            for line in f:
                # skip comment lines.
                if (line[0] == "#"):
                    continue

                # Split line into coordinates.
                line_data = line.split(';')
                
                # From the line, only keep the location.
                line_data = line_data[1:4]
                
                # Convert coordinates from type string to type float.
                line_data = [float(coord) for coord in line_data]
                
                # Add them to the main coordinates array.
                coordinates.append(line_data)

    except Exception as e:
        print("ERROR: " + str(e))

    return coordinates


def read_files(directory):
    # Read all files from directory.
    files = glob.glob(directory + "/*.dat")
    files = sorted(files)
    return files

def main():
    parser = argparse.ArgumentParser(description='Accuracy')
    parser.add_argument('zero_dir', type=str, help='Theta=0.0 directory')
    parser.add_argument('theta_dir', type=str, help='Theta directory')
    args = parser.parse_args()

    files_0 = read_files(args.zero_dir)
    files_theta = read_files(args.theta_dir)

    iterations_0 = []
    for file in files_0:
        iterations_0.append(get_coordinates(file))

    iterations_theta = []
    for file in files_theta:
        iterations_theta.append(get_coordinates(file))

    if (len(iterations_0) != len(iterations_theta)):
        print("There is a difference in number of iterations!")
        sys.exit(-1)

    errors = []
    for i in range(len(iterations_0)):
        errors.append(avg_distance(iterations_0[i], iterations_theta[i]))

    print(np.average(errors))

if __name__ == '__main__':
    main()
