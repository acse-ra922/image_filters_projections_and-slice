//
// Created by Wang, Yuyang on 19/03/2023.
//

#include "Image.h"
#include <iostream>
#include <cmath>

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


// other methods
unsigned char*Image::padding(unsigned char *dat) {
    int w = this->width;
    int h = this->height;
    // padding 0 around
    unsigned char p_data[(h+2)*(w+2)];
    for(int i=0; i<h+2; ++i){
        for(int j=0; j<w+2; ++j){
            if(i==0 || i==h+1){p_data[i*w+j]=static_cast<unsigned char>(0);}
            else if(j==0 || j==w+1){p_data[i*w+j]=static_cast<unsigned char>(0);}
            else {p_data[i*w+j] = dat[(i-1)*w+(j-1)];}
        }
    }
    return p_data;
}




double* Image::conv(double*pad_img_grid, double *kernel){
    int w = this->width;
    int h = this->height;
    double result[w*h];

    for (int i = 1; i < h+1; i++){
        for(int j = 1; j < w+1; j++){
            double sum = 0.0;
            sum += (pad_img_grid+i-1)[j-1]*kernel[0] + (pad_img_grid+i-1)[j]*kernel[1] + (pad_img_grid+i-1)[j+1]*kernel[2];
            sum += (pad_img_grid+i)[j-1]*kernel[3] + (pad_img_grid+i)[j]*kernel[4] + (pad_img_grid+i)[j+1]*kernel[5];
            sum += (pad_img_grid+i+1)[j-1]*kernel[6] + (pad_img_grid+i+1)[j]*kernel[7] + (pad_img_grid+i+1)[j+1]*kernel[8];
            result[(i-1)*w+(j-1)] = sum;
            //std::cout << sum << " ";
        }
    }

    return result;
}
