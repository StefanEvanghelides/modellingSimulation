import cv2
import numpy as np
import glob
import time
import os, sys, shutil


imagesDirectory = "plotting_result"
imagesPath = os.path.abspath(imagesDirectory)

videoDirectory = "video_result"
videoPath = os.path.abspath(videoDirectory)


def create_video():
    img_array = []

    files = glob.glob(imagesPath + "/*.png")
    files = sorted(files)

    print("Reading files from: " + str(imagesPath))
    tstart = time.time()

    for file in files:
        img = cv2.imread(file)
        height, width, layers = img.shape
        size = (width,height)
        img_array.append(img)

    videoFilePath = os.path.join(videoPath, "video.avi")
    out = cv2.VideoWriter(videoFilePath, cv2.VideoWriter_fourcc(*'DIVX'), 15, size)

    for i in range(len(img_array)):
        out.write(img_array[i])
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
        create_video() # This uses the global imagesPath
    else:
        print("\n      Images directory does not exists! Cannot create video!")
        print("HINT: Images directory is generated automatically after running the plotting script!\n")
