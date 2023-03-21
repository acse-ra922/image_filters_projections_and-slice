//
// Created by Wang, Yuyang on 19/03/2023.
// Implemented by Yang, Yi on 21/03/2023.
//

#pragma once

#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_PROJECTION_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_PROJECTION_H


class Projection 
{
private:
	std::string data_dir;
	int width = -1;
	int height = -1;
	int zmin = -1;
	int zmax = -1;
	unsigned char* data = nullptr;

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

	//// Set functions
	//void set_zmin(const int& z_min);
	//void set_zmax(const int& z_max);

	// Orthographic projection functions
	unsigned char* max_ip(int zmin = NULL, int zmax = NULL);
	unsigned char* min_ip(int zmin = NULL, int zmax = NULL);
	unsigned char* avg_ip(int zmin = NULL, int zmax = NULL);
};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_PROJECTION_H
