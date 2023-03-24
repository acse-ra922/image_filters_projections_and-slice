// Group-Dijkstra
// Xuefei Mi (xm421)
// Yuyang Wang (yw22)
// Chaofan Wu (cw522)
// Yi Yang (yy3222)
// Rubab Atwal (ra922)


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
            if(i==0 || i==h+1){p_data[i*(w+2)+j]=static_cast<unsigned char>(0);}
            else if(j==0 || j==w+1){p_data[i*(w+2)+j]=static_cast<unsigned char>(0);}
            else {p_data[i*(w+2)+j] = dat[(i-1)*w+(j-1)];}
        }
    }
    return p_data;
}
