//
// Created by Wang, Yuyang on 19/03/2023.
//

#include "Volume.h"

// Constructor
Volume::Volume(int w, int h, int d) {
    this->set_width(w);
    this->set_height(h);
    this->set_depth(d);
}

// Destructor
Volume::~Volume() {

}

int Volume::get_width() { return this->width; }

int Volume::get_height() { return this->height; }

int Volume::get_depth() { return this->depth; }

void Volume::set_width(int w) { this->width = w; }

void Volume::set_height(int h) { this->height = h; }

void Volume::set_depth(int d) { this->depth = d; }