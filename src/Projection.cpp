//
// Created by Wang, Yuyang on 19/03/2023.
// Implemented by Yang, Yi on 21/03/2023.
//

#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <filesystem>
namespace fs = std::filesystem;

#include "Projection.h"

// Constructor
Projection::Projection(const std::string directory):
	data_dir(directory)
{}

// Destructor
Projection::~Projection()
{
	delete data;
}

// Get functions
std::string Projection::get_data_dir()
{
	return this->data_dir;
}

int Projection::get_width()
{
	return this->width;
}

int Projection::get_height()
{
	return this->height;
}

int Projection::get_zmin()
{
	return this->zmin;
}

int Projection::get_zmax()
{
	return this->zmax;
}

//// Set functions
//void Projection::set_zmin(const int& z_min)
//{
//	if (z_min < 0)
//	{
//		std::cerr << "Invalid minimum z\n";
//		return;
//	}
//	this->zmin = z_min;
//}
//
//void Projection::set_zmax(const int& z_max)
//{
//	if (z_max < 0)
//	{
//		std::cerr << "Invalid maximum z\n";
//		return;
//	}
//	this->zmax = z_max;
//}

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
unsigned char* Projection::max_ip(int zmin, int zmax)
{
    int c;

    // Read in all file names
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(this->data_dir))
        files.push_back(entry.path().u8string());

    // Calculate minimum and maximum z
    int file_size = files.size();
    if (zmin == NULL)
        this->zmin = 0;
    else
        this->zmin = fmax(zmin, 0);
    if (zmax == NULL)
        this->zmax = file_size;
    else
        this->zmax = fmin(zmax, file_size);

    // Define and write output
    if (this->data)
        stbi_image_free(this->data);
    this->data = stbi_load(files[this->zmin].c_str(), &this->width, &this->height, &c, 0);

    for (int i = this->zmin + 1; i < this->zmax; i++)
    {
        // Load a new image and compare with current max
        int wi, hi, ci;
        unsigned char* data;
        data = stbi_load(files[i].c_str(), &wi, &hi, &ci, 0);
        for (int y = 0; y < hi; ++y)
        {
            for (int x = 0; x < wi; ++x)
            {
                // Get the value at position (x, y)
                int pixel_index = (y * wi + x) * ci;
                unsigned char data_pixel_value = data[pixel_index];
                int data_val = data_pixel_value;
                unsigned char out_pixel_value = this->data[pixel_index];
                int out_val = out_pixel_value;

                // Compare and write the results
                unsigned char out_pixel = fmax(out_val, data_val);
                this->data[pixel_index] = out_pixel;
            }
        }
        // Deallocate memory
        stbi_image_free(data);
    }

    return this->data;
}

/*
    Minimum intensity projection

    @param
    ----------
    zmin, zmax: minimum and maximum z coordinates of the user specified thin slab

    @return
    ----------
    data: output projection data
*/
unsigned char* Projection::min_ip(int zmin, int zmax)
{
    int c;

    // Read in all file names
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(this->data_dir))
        files.push_back(entry.path().u8string());

    // Calculate minimum and maximum z
    int file_size = files.size();
    if (zmin == NULL)
        this->zmin = 0;
    else
        this->zmin = fmax(zmin, 0);
    if (zmax == NULL)
        this->zmax = file_size;
    else
        this->zmax = fmin(zmax, file_size);

    // Define and write output
    if (this->data)
        stbi_image_free(this->data);
    this->data = stbi_load(files[this->zmin].c_str(), &this->width, &this->height, &c, 0);

    for (int i = this->zmin + 1; i < this->zmax; i++)
    {
        // Load a new image and compare with current min
        int wi, hi, ci;
        unsigned char* data;
        data = stbi_load(files[i].c_str(), &wi, &hi, &ci, 0);
        for (int y = 0; y < hi; ++y)
        {
            for (int x = 0; x < wi; ++x)
            {
                // Get the value at position (x, y)
                int pixel_index = (y * wi + x) * ci;
                unsigned char data_pixel_value = data[pixel_index];
                int data_val = data_pixel_value;
                unsigned char out_pixel_value = this->data[pixel_index];
                int out_val = out_pixel_value;

                // Compare and write the results
                unsigned char out_pixel = fmin(out_val, data_val);
                this->data[pixel_index] = out_pixel;
            }
        }
        // Deallocate memory
        stbi_image_free(data);
    }

    return this->data;
}

/*
    Average intensity projection

    @param
    ----------
    zmin, zmax: minimum and maximum z coordinates of the user specified thin slab

    @return
    ----------
    data: output projection data
*/
unsigned char* Projection::avg_ip(int zmin, int zmax)
{
    int c;

    // Read in all file names
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(this->data_dir))
        files.push_back(entry.path().u8string());

    // Calculate minimum and maximum z
    int file_size = files.size();
    if (zmin == NULL)
        this->zmin = 0;
    else
        this->zmin = fmax(zmin, 0);
    if (zmax == NULL)
        this->zmax = file_size;
    else
        this->zmax = fmin(zmax, file_size);

    // Define and write output
    if (this->data)
        stbi_image_free(this->data);
    this->data = stbi_load(files[this->zmin].c_str(), &this->width, &this->height, &c, 0);
    std::vector<double> out_vals;
    for (int y = 0; y < this->height; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            int pixel_index = (y * this->width + x) * c;
            unsigned char out_pixel_value = this->data[pixel_index];
            double out_val = (double)out_pixel_value / (this->zmax - this->zmin);
            out_vals.push_back(out_val);
        }
    }

    // Write to output
    for (int i = this->zmin + 1; i < this->zmax; i++)
    {
        // Load a new image and add to current average
        int wi, hi, ci;
        unsigned char* data;
        data = stbi_load(files[i].c_str(), &wi, &hi, &ci, 0);
        for (int y = 0; y < hi; ++y)
        {
            for (int x = 0; x < wi; ++x)
            {
                int pixel_index = (y * wi + x) * ci;
                unsigned char data_pixel_value = data[pixel_index];
                int data_val = data_pixel_value;
                out_vals[pixel_index] += (double)data_val / (this->zmax - this->zmin);
            }
        }
        // Deallocate memory
        stbi_image_free(data);
    }

    // Cast double to int for output
    for (int y = 0; y < this->height; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            int pixel_index = (y * this->width + x) * c;
            unsigned char out_pixel_value = (int)out_vals[pixel_index];
            this->data[pixel_index] = out_pixel_value;
        }
    }

    return this->data;
}