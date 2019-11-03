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
