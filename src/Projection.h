// Group-Dijkstra
// Xuefei Mi (xm421)
// Yuyang Wang (yw22)
// Chaofan Wu (cw522)
// Yi Yang (yy3222)
// Rubab Atwal (ra922)

#pragma once

#include "stb_image.h"

#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_PROJECTION_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_PROJECTION_H


class Projection 
{
private:
	std::string data_dir;
	int file_size = -1;
	int width = -1;
	int height = -1;
	int zmin = -1;
	int zmax = -1;
	unsigned char* data = nullptr;

	// Helper function
	/*
	Compute correct z range of the user specified thin slab

	@param
	----------
	zmin, zmax: minimum and maximum z specified by user
	*/
	void find_z_range(const int& zmin, const int& zmax);

public:
	// Constructor
	Projection(const std::string directory);

	// Destructor
	~Projection();

	// Get functions
	std::string get_data_dir() const;
	int get_width() const;
	int get_height() const;
	int get_zmin() const;
	int get_zmax() const;
	int get_file_size() const;

	// Orthographic projection functions

	/*
	Maximum intensity projection

	@param
	----------
	zmin, zmax: minimum and maximum z coordinates of the user specified thin slab

	@return
	----------
	data: output projection data
	*/
	unsigned char* max_ip(int zmin = NULL, int zmax = NULL);

	/*
	Minimum intensity projection

	@param
	----------
	zmin, zmax: minimum and maximum z coordinates of the user specified thin slab

	@return
	----------
	data: output projection data
	*/
	unsigned char* min_ip(int zmin = NULL, int zmax = NULL);

	/*
	Average intensity projection

	@param
	----------
	zmin, zmax: minimum and maximum z coordinates of the user specified thin slab

	@return
	----------
	data: output projection data
	*/
	unsigned char* avg_ip(int zmin = NULL, int zmax = NULL);
};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_PROJECTION_H
