# Modelling and Simulation
This repository contains the project for the Modelling and Simulation course.

## Topic: Simulating Colliding Galaxies
It is recommended to use Docker to run this application (see below). How to run manually:
```
mkdir build
cd build
cmake ..
make
cd ..
```
Then you can run the program as follows:
```
./build/src/run [options] 

Optional arguments:
-h --help       	shows help message and exits
-v --version    	prints version information and exits
-d --debug      	increase output verbosity (default: false)
-i --iterations 	Number of iterations (default: 500)
-s1 --stars1    	Number of stars in the first galaxy (default: 1000)
-s2 --stars2    	Number of stars in the second galaxy (default: 1000)
-t --theta      	Theta value, based on the Barnes-Hut algorithm (default: 0.5)
-p --plot       	Automatically plot the stars (default: false)

```
The data will be saved in `data/`. The simulation can now be visualized as follows:
```
usage: python plotting/plot.py [-h] [directory]

positional arguments:
  directory   Specify the data directory(ies). If it's not specified, then
              data from all directories will be plotted. Note: Program will
              pattern match the argument

optional arguments:
  -h, --help  show this help message and exit

```
This plots the frames. A video can be constructed from the frames by running:
```
python video/video.py [-h] [directory]
```
Some example videos are stored in `~Saved_Results/`.

### Running the application using Docker containers
It is currently possible to run the application in Docker containers. There are 2 ways to do this:

1. Easy way: Run `docker-compose up --build modsim`

  This will run the containers binding mounted directories from the local system (path is inside the project to the directories "data" and, respectively, "plotting_result") to the container. The results will therefore be visible immediately to the local host. Currently it is not possible to directly pass arguments to the program, put your desired arguments in `docker-compose.yaml`.

2. Hard way: Run `init.bat` (for Windows) or `init.sh` (for Unix): this will create the volumes that will store the data, according to the Docker specifications. Then, execute `docker-compose -f docker-compose-w.yaml up modsim`, which will execute the program and store data inside the volumes. Now, if desired, the data can be copied into the local host in the directories "data" and, respectively, "plotting_result" using the script `copy-data-to-local.bat` (for Windows) or `copy-data-to-local.sh` (for Unix)
