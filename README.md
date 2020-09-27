# Modelling and Simulation
This repository contains the project for the Modelling and Simulation course.

## Topic: Simulating Colliding Galaxies
How to run:
```
make clean
make
./run <galaxy1size> <galaxy2size> <iterations> <theta>
```
The data will be saved in `data/`. The simulation can now be visualized as follows:
```
python plotting/plot.py
```
This plots the frames. A video can be constructed from the frames by running:
```
python video/video.py
```
Some example videos are stored in `~Saved_Results/`.

### Running the application using Docker containers
It is currently possible to run the application in Docker containers. There are 2 ways to do this:

1. Easy way: Run `docker-compose up --build modsim`

  This will run the containers binding mounted directories from the local system (path is inside the project to the directories "data" and, respectively, "plotting_result") to the container. The results will therefore be visible immediately to the local host.

2. Hard way: Run `init.bat` (for Windows) or `init.sh` (for Unix): this will create the volumes that will store the data, according to the Docker specifications. Then, execute `docker-compose -f docker-compose-w.yaml up modsim`, which will execute the program and store data inside the volumes. Now, if desired, the data can be copied into the local host in the directories "data" and, respectively, "plotting_result" using the script `copy-data-to-local.bat` (for Windows) or `copy-data-to-local.sh` (for Unix)
