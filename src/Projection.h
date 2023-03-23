//
// Created by Wang, Yuyang on 19/03/2023.
// Written by Yang, Yi on 21/03/2023.
//

#pragma once

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
	void find_z_range(const int& zmin, const int& zmax);

public:
	// Constructor
	Projection(const std::string directory);

	// Destructor
	~Projection();

	// Get functions
	std::string get_data_dir();
	int get_width();
	int get_height();
	int get_zmin();
	int get_zmax();
	int get_file_size();

	// Orthographic projection functions
	unsigned char* max_ip(int zmin = NULL, int zmax = NULL);
	unsigned char* min_ip(int zmin = NULL, int zmax = NULL);
	unsigned char* avg_ip(int zmin = NULL, int zmax = NULL);
};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_PROJECTION_H
