import cv2
import numpy as np
import glob
import time
import os, sys, shutil


imagesDirectory = "plotting_result"
imagesPath = os.path.abspath(imagesDirectory)

videoDirectory = "video_result"
videoPath = os.path.abspath(videoDirectory)

FRAMES_PER_SECOND = 20

def create_video(files):
    print("Reading files from: " + str(imagesPath))
    tstart = time.time()

    # Retrieve the sizes of an image.
    # It is assumed that all images have the same sizes.
    file_0 = cv2.imread(files[0])
    height, width, layers = file_0.shape
    size = (width,height)

    # Create the video
    videoFilePath = os.path.join(videoPath, "video.mp4")
    out = cv2.VideoWriter(videoFilePath, cv2.VideoWriter_fourcc(*'mp4v'), FRAMES_PER_SECOND, size)

    for file in files:
        img = cv2.imread(file)
        out.write(img)
    
    # Release the video
    out.release()

    elapsed_time = time.time() - tstart
    print("Combined " + str(len(files)) + " images in " + str(elapsed_time) + " seconds.")


if __name__ == '__main__':
    # Remove the existing Video_result directory, create an empty one
    if os.path.exists(videoPath):
        shutil.rmtree(videoPath)
    if not os.path.exists(videoPath):
        os.makedirs(videoPath)

    if os.path.exists(imagesPath):
        files = glob.glob(imagesPath + "/*.png")
        files = sorted(files)

        if len(files) > 0:
            create_video(files) # This uses the global imagesPath
        else:
            print("\n      Images directory is empty! Cannot create video!")
            print("HINT: Plot the stars again after (re)running the program!")

    else:
        print("\n      Images directory does not exists! Cannot create video!")
        print("HINT: Images directory is generated automatically after running the plotting script!\n")
