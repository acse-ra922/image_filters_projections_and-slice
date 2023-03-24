# Advanced Programming Group Project - Dijkstra

**Image Filters, Projections and Slices**

**March 2023**

```angular2html
Xuefei Mi (xm421)
Yuyang Wang (yw22)
Chaofan Wu (cw522)
Yi Yang (yy3222)
Rubab Atwal (ra922)
```

------

## Implementation Overview

This is a C++ program that applies a range of image filters and orthographic projections to 2D input images and 3D data volume.

For 2D images we have the following filters:
+ Color correction
  - Grayscale
  - Automatic colour balance
  - Brightness
  - Histogram equalization
+ Blur
  - Median blur
  - Box blur
  - Gaussian blur
+ Edge detection
  - Sobel
  - Prewitt
  - Scharr
  - Roberts’ Cross

For 3D data we have the follwing functionalities:
+ Filter
  - 3D Gaussian
  - 3D Median
+ Projection
  - Maximum intensity projection
  - Minimum intensity projection
  - Average intensity projection
  - Projection over a thin slab
+ Slicing
  - Slicing in the x-z plane
  - Slicing in the y-z plane

------

## Code Structure

We have implemented one main function and 6 Classes, their names and functionalities as follows:

 - Image - represents an image and memory and sets its attributes

 - Filter - performs all 2D filters on an image

 - Volume - construct 3D volume data, write processed volume into images, apply 3D filters

 - Projection - computes 3 orthographic projections on 3D data volume. 

 - Slice - slices 3D volume data

 - Tests - tests all the functions defined in Filter.cpp, Volume.cpp, Slice.cpp and Projection.cpp

------

## Requirements
+ Visual Studio (Windows): C++ >= 17
+ Clion (Mac): see `CmakeLists.txt`

------

## Usage

#### MacOS
+ 2D filter
```
cd executable
./main_2Dfilter
```

+ 3D Gaussian/Median
```
cd executable
./main_3Dfilter ../Scans/confuciusornis ../Output/confuciusornis
```

+ Projection
```
cd executable
./main_Projection
```

------

## Documentation and Report

The documentation for the project describing the classes, functions and their usage can be found in the "docs/" folder. 
The report for this project can also be found in the "/docs" folder.
