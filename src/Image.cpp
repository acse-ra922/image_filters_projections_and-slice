//
// Created by Wang, Yuyang on 19/03/2023.
//

#include "Image.h"

// Constructor
Image::Image(int w, int h, int c, unsigned char* dat) {
    this->set_width(w);
    this->set_height(h);
    this->set_channel(c);
    this->set_data(dat);
}

// Destructor
Image::~Image() {

}

int Image::get_width() { return this->width; }

int Image::get_height() { return this->height; }

int Image::get_channel() { return this->channel; }

unsigned char* Image::get_data() {return this->data;}

void Image::set_width(int w) { this->width = w; }

void Image::set_height(int h) { this->height = h; }

void Image::set_channel(int c) { this->channel = c; }

void Image::set_data(unsigned char *dat) {this->data = dat;}