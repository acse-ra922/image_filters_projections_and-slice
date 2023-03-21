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

// get methods
int Image::get_width() { return this->width; }

int Image::get_height() { return this->height; }

int Image::get_channel() { return this->channel; }

unsigned char* Image::get_data() {return this->data;}

double *Image::get_out() {return this->out;}

// set methods
void Image::set_width(int w) { this->width = w; }

void Image::set_height(int h) { this->height = h; }

void Image::set_channel(int c) { this->channel = c; }

void Image::set_data(unsigned char *dat) {this->data = dat;}

void Image::set_out(double *dat) {this->out = dat;}

// other methods
double *Image::change2doubledata(unsigned char *dat) {
    // padding 0 around
    double d_data[this->height+2][this->width+2];
    for(int i=1; i<this->height+1; ++i){
        for(int j=1; j<this->width+1; ++j){
            d_data[i][j] = static_cast<double>(dat[(i-1)*this->width+(j-1)]);
        }
    }
    return d_data[0];
}

unsigned char *Image::change2data(double *d_data) {

}

double* Image::conv(double *pad_img_grid, double *kernel){
    double * result = new double[this->width*this->height];

    for (int i = 1; i < this->height+1; i++){
        for(int j = 1; j < this->width+1; j++){
            double sum = 0.0;
            sum += (pad_img_grid+i)[j]*kernel[0] + (pad_img_grid+i)[j+1]*kernel[1] + (pad_img_grid+i)[j+2]*kernel[2];
            sum += (pad_img_grid+i+1)[j]*kernel[3] + (pad_img_grid+i+1)[j+1]*kernel[4] + (pad_img_grid+i+1)[j+2]*kernel[5];
            sum += (pad_img_grid+i+2)[j]*kernel[6] + (pad_img_grid+i+2)[j+1]*kernel[7] + (pad_img_grid+i+2)[j+2]*kernel[8];
            result[(i-1)*this->width+(j-1)] = sum;
        }
    }

    return result;
}