# Advanced Programming Group Project - Dijkstra

**Image Filters, Projections and Slices**

**March 2023**

## Implementation Overview

This is a C++ program that applies a range of image filters and orthographic projections to 2D input images and 3D data volume.

For 2D images we have the following filters:

 - Grayscale
 - Automatic colour balance
 - Brightness
 - Histogram equalization
 - Median blur
 - Box blur
 - Gaussian blur
 - Sobel
 - Prewitt
 - Scharr
 - Roberts’ Cross

For 3D data we have the follwing functionalities:

 - 3D Gaussian
 - 3D Median
 - Maximum intensity projection
 - Minimum intensity projection
 - Average intensity projection
 - Projection over a thin slab
 - Slicing in the x-z or y-z plane

## Code Structure

We have implemented one main function and 6 Classes, their names and functionalities as follows:

 - Image - represents an image and memory and sets its attributes

 - Filter - performs all 2D filters on an image

 - Volume - construct 3D volume data, write processed volume into images, apply 3D filters

 - Projection - computes 3 orthographic projections on 3D data volume. 

 - Slice - slices 3D volume data

 - Tests - tests all the functions defined in Filter.cpp, Volume.cpp, Slice.cpp and Projection.cpp


## Requirements

C++ >= 17

## Usage
