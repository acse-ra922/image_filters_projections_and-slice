#include <iostream>
#include <memory>
#include <string>
#include "stb_image.h"
#include "stb_image_write.h"
#include "Volume.h"
#include "Slice.h"


// constructor
Slice::Slice() : Volume() {}

Slice::Slice(std::string slice_plane, int slice_pos, Volume &v) : slice_plane(slice_plane), slice_pos(slice_pos) {
    if (slice_plane != "x-z" && slice_plane != "y-z") {
        throw std::invalid_argument("Invalid slice plane. Please choose either 'x-z' or 'y-z'.");
    }
    else
    {
        if (slice_plane == "x-z" && (slice_pos < 0 || slice_pos >= v.get_height())) {
            throw std::invalid_argument("Invalid slice position. Please choose between 0 and volume height, [0, height).");
        }
        else if (slice_plane == "y-z" && (slice_pos < 0 || slice_pos >= v.get_width())) {
            throw std::invalid_argument("Invalid slice position. Please choose between 0 and volume width, [0, width).");
        }
    }
}

// Destructor
Slice::~Slice() {}

// get function
std::string Slice::get_slice_plane() const { return this->slice_plane; }

int Slice::get_slice_pos() const { return this->slice_pos; }

void Slice::get_slice_pic(Volume& v) {

    int idx = 0;
    // slice along y-z 
    if (this->slice_plane.compare("y-z") == 0) {
        // create a new unique pointer
        this->slice_pic = std::make_unique<unsigned char[]>(v.get_height() * v.get_depth() * v.get_channel());

        // create the slice_pic
        // y -> i
        for (int j = 0; j < v.get_depth(); j++) {
            // z -> j
            for (int i = 0; i < v.get_height(); i++) {
                for (int ch = 0; ch < v.get_channel(); ch++) {
                    // index for the Volume
                    idx = (this->slice_pos + i * v.get_width() + j * v.get_img_size()) * v.get_channel() + ch;
                    this->slice_pic[(i * v.get_depth() + j) * v.get_channel() + ch] = v.get_data()[idx];

                    //idx = this->slice_pos + i * v.get_width() + j * v.get_img_size();
                    //this->slice_pic[i * v.get_depth() + j] = v.get_data()[idx];
                }
            }
        }
    }
        // slice along x-z
    else if (this->slice_plane.compare("x-z") == 0) {
        this->slice_pic = std::make_unique<unsigned char[]>(v.get_width() * v.get_depth() * v.get_channel());

        // create the slice_pic
        // z -> i
        for (int i = 0; i < v.get_depth(); i++) {
            // x -> j
            for (int j = 0; j < v.get_width(); j++) {
                for (int ch = 0; ch < v.get_channel(); ch++) {
                    // index for the Volume
                    idx = (j + this->slice_pos * v.get_width() + (v.get_depth() - 1 - i) * v.get_img_size()) * v.get_channel() + ch;
                    this->slice_pic[(i * v.get_width() + j) * v.get_channel() + ch] = v.get_data()[idx];

                    //idx = j + this->slice_pos * v.get_width() + (v.get_depth() - 1 - i) * v.get_img_size();
                    //this->slice_pic[i * v.get_width() + j] = v.get_data()[idx];
                }
            }
        }
    }
    // output the slice image
    store_pic(v);
}

//set function
void Slice::set_slice_plane(std::string& slice_plane) {
    // handle invalid slice_plane error
    if (slice_plane != "x-z" && slice_plane != "y-z") {
        throw std::invalid_argument("Invalid slice plane. Please choose either 'x-z' or 'y-z'.");
    }

    // assign appropriate slice plane
    this->slice_plane = slice_plane;
}

void Slice::set_slice_pos(int slice_pos, Volume& v) {
    // handle slice_pos out of range error
    if (slice_plane == "x-z" && (slice_pos < 0 || slice_pos >= v.get_height())) {
        throw std::invalid_argument("Invalid slice position. Please choose between 0 and volume height, [0, height).");
    }
    else if (slice_plane == "y-z" && (slice_pos < 0 || slice_pos >= v.get_width())) {
        throw std::invalid_argument("Invalid slice position. Please choose between 0 and volume width, [0, width).");
    }

    // assign appropriate slice position
    this->slice_pos = slice_pos;
}

// store sliced_img
void Slice::store_pic(Volume& v) {

    std::string filename = this->slice_plane + "_" + std::to_string(this->slice_pos)+".png";

    int success;

    // Save image to new filename
    if (this->slice_plane.compare("y-z") == 0) {
        success = stbi_write_png(filename.c_str(), v.get_depth(), v.get_height(), v.get_channel(), this->slice_pic.get(), v.get_depth() * v.get_channel());
    }
    else if (this->slice_plane.compare("x-z") == 0) {
        success = stbi_write_png(filename.c_str(), v.get_width(), v.get_depth(), v.get_channel(), this->slice_pic.get(), v.get_width() * v.get_channel());
    }
}
