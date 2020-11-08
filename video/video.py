import cv2
import numpy as np
import glob
import time
import os, sys, shutil
import argparse


imagesDirectory = "plotting_result"
imagesPath = os.path.abspath(imagesDirectory)

videoDirectory = "video_result"
videoPath = os.path.abspath(videoDirectory)

FRAMES_PER_SECOND = 20


# Arguments
parser = argparse.ArgumentParser(prog="ModSim", allow_abbrev=True)
parser.add_argument("directory", nargs="?", default="*",
                    help="Specify the data directory(ies). If it's not specified, \
                            than data from all directories will be plotted.\
                            Note: Program will pattern match the argument")
args = parser.parse_args()


def create_video(files, images_directory=imagesPath, video_basename=videoPath):
    print("Reading files from: " + str(images_directory))
    tstart = time.time()

    # Retrieve the sizes of an image.
    # It is assumed that all images have the same sizes.
    file_0 = cv2.imread(files[0])
    height, width, layers = file_0.shape
    size = (width,height)

    # Create the video as MP4
    videoFilePath = os.path.join(videoPath, video_basename)
    videoFilePath = videoFilePath + ".mp4"
    out = cv2.VideoWriter(videoFilePath, cv2.VideoWriter_fourcc(*'mp4v'), FRAMES_PER_SECOND, size)

    for file in files:
        img = cv2.imread(file)
        out.write(img)
    
    # Release the video
    out.release()

    elapsed_time = time.time() - tstart
    print("Combined " + str(len(files)) + " images in " + str(elapsed_time) + " seconds.")


if __name__ == '__main__':
    if not os.path.exists(imagesPath):
        print("\n      Images directory does not exists! Cannot create video!")
        print("HINT: Images directory is generated automatically after running the plotting script!\n")
        sys.exit(0)

    # Read the directory names. 
    # The first element was the main directory. Remove it.
    images_directories = [x[0] for x in os.walk(imagesPath)]
    images_directories = images_directories[1:]

    # Check the directory passed as argument.
    if args.directory is not "*":
        images_directories = [x for x in images_directories if args.directory in x]

    # Read all files from directory.
    for images_dir in images_directories:
        # If the results path does not exit, then create it.
        if not os.path.exists(videoPath):
            os.makedirs(videoPath)
        
        # Keep only the base name, not the full path
        images_dir_base = os.path.basename(images_dir)

        # Create a new directory based on the current data directory.
        video_basename = os.path.join(videoPath, images_dir_base)

        files = glob.glob(images_dir + "/*.png")
        files = sorted(files)

        if len(files) < 1:
            print("\n      Images directory is empty! Cannot create video!")
            print("HINT: Plot the stars again after (re)running the program!")
            sys.exit(0)

        create_video(files, images_directory=images_dir, video_basename=video_basename)
